# CREATE TABLE log (id int PRIMARY KEY, A int, B int, C int, D int, E int, F int, X int, W int);
# DROP TABLE log;
# SELECT * FROM log;

require 'pg'

def conexao_banco
  begin
    @connection = PG::Connection.new({
      :host => :localhost, 
      :user => :postgres, 
      :dbname => :dbii, 
      :port => 5432, 
      :password => "postgres"
    })
  rescue PG::Error => err
    puts err.message
  end
end

def insere_dados_iniciais
  # Separo dados iniciais da primeira string
  @dados_iniciais = @dados.last.split(" | ").collect { |value| value.gsub(/\D/, '') }
  # Faço a inserção dos dados iniciais
  @connection.exec("INSERT INTO log VALUES(1, #{@dados_iniciais.dig(0)}, #{@dados_iniciais.dig(1)}, #{@dados_iniciais.dig(2)}, #{@dados_iniciais.dig(3)}, #{@dados_iniciais.dig(4)}, #{@dados_iniciais.dig(5)}, #{@dados_iniciais.dig(6)}, #{@dados_iniciais.dig(7)})")
end

def verefica_e_ou_salva_dado transacao
  # Pega dados separados
  transacao = transacao.downcase.delete("<>").split(",")
  # Verefica se já está no banco
  valor = @connection.exec("SELECT #{transacao.dig(2)} FROM log WHERE id = #{transacao.dig(1)};")
  # Pega o valor da consulta
  valor = valor.first[transacao.dig(2)]

  # Imprime que realizou o redo
  printf "Transação #{transacao.dig(0)} realizou Redo \n"

  # Verefica se os dados são iguais
  if valor.to_i != transacao.dig(3).to_i
    # Imprime valores
    printf "O dado #{transacao.dig(2)} era #{valor.to_i} e foi atualizado para #{transacao.dig(3).to_i} \n"
    # Atualiza no banco
    @connection.exec("UPDATE log SET #{transacao.dig(2)} = #{transacao.dig(3)} WHERE id = #{transacao.dig(1)};")
  else
    printf "Esse dado é o mesmo que o salvo no banco \n"
  end

  printf "\n"
end

# Conecta ao banco
conexao_banco()

# Abre arquivo
@arquivo = File.open('teste_final')
# Faz map em dados e reverte a ordem
@dados = @arquivo.readlines.map(&:chomp).reverse()

# Cria variavel para guardar transações que estão ou foram abertas
@transacao_aberta = []
# Cria variavel para guardar quem vai ser feito o redo
@redo = []
# Cria variavel para guardar updates que vão ser feitos
@transacoes = []

# Insere dados iniciais
insere_dados_iniciais()

# Percorre o array do arquivo, que está invertido
@dados.each_with_index do |dado, index|
  # Caso já tiver passado por um end checkpoint define como verdadeiro
  @end_checkpoint = true if dado.downcase.match?(/end ckpt/)

  # Caso já tiver passado por um end checkpoint ve se é um start checkpoint
  if @end_checkpoint && dado.downcase.match?(/start ckpt/)

    # Salva index do array do start checkpoint
    @start_checkpoint_index = index

    # Salva transação como aberta
    @transacao_aberta << dado.downcase.gsub(/start ckpt|start checkpoint/, "").delete("<( )>").split(",")

    # Para de percorrer o arquivo
    break
  end
  
end

# Percorre arquivo do checkpoint até o final
@dados[0..@start_checkpoint_index].reverse().each do |dado|
  # Caso o dado for uma start transação coloca que foi aberta
  @transacao_aberta << dado.downcase.gsub(/start /, "").delete("<>") if dado.downcase.match?(/<start t[0-9]>/)
  # Caso o dado for o commit da transação e ela estiver como aberta é colocada para fazer o redo
  @redo << dado.downcase.gsub(/commit /, "").delete("<>") if dado.downcase.match?(/<commit t[0-9]>/) && @transacao_aberta.flatten.include?( dado.downcase.gsub(/commit /, "").delete("<>") )
end

# Pega as transações que vai ser feito o redo
@redo.each do |transation|
  @transacoes << @dados.filter {|dado| dado.downcase.match(/<#{transation},/)}
end

# Refaz transações 
@transacoes.flatten.each do |transacao| 
  verefica_e_ou_salva_dado(transacao)
end
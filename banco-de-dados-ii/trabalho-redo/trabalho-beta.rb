require 'pg'
# CREATE TABLE log(id int PRIMARY KEY, A int, B int, C int, D int, E int);
# INSERT INTO log VALUES(1, 5, 10, 20, 30, 40)

def db_connect
  begin
    @connection = PG::Connection.new({
      :host => :localhost, 
      :user => :postgres, 
      :dbname => :postgres, 
      :port => 5432, 
      :password => "postgres"
    })
  rescue PG::Error => err
    puts err.message
  end
end

def db_update operation
  printf "Transação #{operation.dig(0)} realizou Redo \n"
  @connection.exec("UPDATE log SET #{operation.dig(2)} = #{operation.dig(3)} WHERE id = #{operation.dig(1)};")
end

def formated_file
  # Le arquivo
  file = File.open('teste_oficial.txt')
  @file_data = file.readlines.map(&:chomp)

  # Inicia valores
  @start_checkpoints = search_in_file( /start checkpoint/ )
  @end_checkpoints = search_in_file( /end checkpoint/ )
  @start_transations = search_in_file(/start t[0-9]/)
  @commit_transations = search_in_file(/commit t[0-9]/)
  @operations = search_in_file(/<t[0-9]/)
end

def search_in_file regex
  @file_data.select { |line_in_file| line_in_file.downcase.match(regex) }
end

# Faz conexão com o banco
db_connect()
# Formata arquivo e atribui valores as variaveis iniciais
formated_file()
# Cria Variaveis
@checkpoint_transations_opened = []
@transations_commited = []

@start_checkpoints.reverse.each do |checkpoint|
  if @checkpoint_transations_opened.empty?

    # Percorre a lista para buscar o ultimo checkpoint
    @file_data.each_with_index do |primary_data, primary_index|
      if checkpoint.include?(primary_data)
        
        # Percorre a partir do checkpoint para vereficar se ele foi concluido e se iniciou uma nova transação
        @file_data[primary_index..(@file_data.length - 1)].each_with_index do |secound_data, secound_index|
          if !@end_checkpoints.empty? && @end_checkpoints.last.include?(secound_data)

            # Salva dados do checkpoint que vai precisar fazer o redo
            @checkpoint_transations_opened << primary_data.downcase.gsub(/start checkpoint /, '').delete('<( )>').split(',')
          end
          
          if @start_transations.last.include?(secound_data)
            # Salva novas transações para fazer o redo se for commitadas
            @checkpoint_transations_opened << secound_data.gsub(/start /, '').delete('<>')
          end

          if @commit_transations.include?(secound_data)
            @transations_commited << secound_data.gsub(/commit /, '').delete('<>')
          end
        end
      end
    end
  end
end

# Pega transações que ficaram em aberto no ultimo checkpoint completo e que foram comitadas 
@redo = @checkpoint_transations_opened.flatten & @transations_commited

printf "#{@checkpoint_transations_opened.flatten.to_s}\n"
printf "#{@transations_commited.to_s}\n"
printf "#{@redo.to_s}\n"

@file_data.each do |data|
  if @operations.include?(data)
    operation = data.delete('< >').split(',')
    if @redo.include?( operation.dig(0) )
      db_update(operation)
    end
  end
end
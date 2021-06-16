require 'rbnacl'
require 'json'
require 'base64'

class CertificadoDigital
  attr_accessor :credenciais, :hash, :hash_cifrado, :chave_privada, :chave_publica
  def initialize credenciais = nil
    self.credenciais    = credenciais
    self.hash           = credenciais.to_s
  end

  # Geração dos dados
  def assinar_com_nova_chave
    self.hash           = RbNaCl::Hash.sha256(self.credenciais.to_s)
    self.chave_privada  = RbNaCl::SigningKey.generate
    self.hash_cifrado   = self.chave_privada.sign(self.hash)
    self.chave_publica  = self.chave_privada.verify_key
  end
  def assinar_com_chave_existente
    self.hash           = RbNaCl::Hash.sha256(self.credenciais.to_s)
    self.chave_privada  = RbNaCl::SigningKey.new(self.chave_privada)
    self.hash_cifrado   = self.chave_privada.sign(self.hash)
    self.chave_publica  = self.chave_privada.verify_key
  end

  # Conversão de dados
  def gerar_base64
    self.hash           = Base64.encode64 self.hash.to_s
    self.hash_cifrado   = Base64.encode64 self.hash_cifrado.to_s
    self.chave_publica  = Base64.encode64 self.chave_publica.to_s
  end
  def gerar_json
    hash_do_certificado = {
      :credenciais    => self.credenciais,
      :hash           => self.hash,
      :hash_cifrado   => self.hash_cifrado,
      :chave_publica  => self.chave_publica,
    }
    json_do_certificado = JSON.generate( hash_do_certificado )
  end
  def analisar_base64
    self.hash           = Base64.decode64 self.hash.to_s
    self.hash_cifrado   = Base64.decode64 self.hash_cifrado.to_s
    self.chave_publica  = Base64.decode64 self.chave_publica.to_s
  end
  def analisar_json json_do_certificado
    certificado_digital = JSON.parse( json_do_certificado )
    self.credenciais    = certificado_digital['credenciais']
    self.hash           = certificado_digital['hash']
    self.hash_cifrado   = certificado_digital['hash_cifrado']
    self.chave_publica  = certificado_digital['chave_publica']
  end

  # Manipulação dos dados para realizar as operações propostas
  def criar_arquivo_com_chave_privada
    puts "Informe o diretorio que deseja salvar sua chave privada \n Default: #{Dir.home}/.certificado_digital/ \n"
    path_chave_privada = gets.chomp.to_s
    path_chave_privada = "#{Dir.home}/.certificado_digital/" if path_chave_privada.empty?

    puts "Informe qual o nome do arquivo da chave privada \n Default: chave-privada \n"
    nome_chave_privada = gets.chomp.to_s
    nome_chave_privada = "chave-privada" if nome_chave_privada.empty?

    Dir.mkdir(path_chave_privada) if !Dir.exists?(path_chave_privada)
    File.open("#{path_chave_privada}/#{nome_chave_privada}", "wb") {|file| file << self.chave_privada }
  end
  def criar_arquivo_com_certificado_digital json_do_certificado
    puts "Informe o diretorio que deseja salvar o certificado digital \n Default: #{Dir.pwd}/ \n"
    path_certificado_digital = gets.chomp.to_s
    path_certificado_digital = "#{Dir.pwd}/" if path_certificado_digital.empty?

    puts "Informe qual o nome do arquivo do certificado digital \n Default: certificado_digital.json \n"
    nome_certificado_digital = gets.chomp.to_s
    nome_certificado_digital = "certificado_digital.json" if nome_certificado_digital.empty?

    File.write("#{Dir.pwd}/#{nome_certificado_digital}", json_do_certificado)
  end
  def atualizar_certificado_digital json_do_certificado
    File.write("#{@path_certificado_digital}", json_do_certificado)
  end
  def abrir_certificado_digital
    puts "Informe o arquivo do certificado que deseja validar \n Default: #{Dir.pwd}/certificado_digital.json \n"
    @path_certificado_digital = gets.chomp.to_s
    @path_certificado_digital = "#{Dir.pwd}/certificado_digital.json" if @path_certificado_digital.empty?

    if File.exists?(@path_certificado_digital)
      certificado_digital = File.open(@path_certificado_digital)
      certificado_digital = certificado_digital.read()
    else
      puts "ERRO: CERTIFICADO NÃO ENCONTRADO"
      exit()
    end
  end
  def abrir_chave_privada
    puts "Informe o arquivo da chave privada que deseja usar para assinar o certificado \n Default: #{Dir.home}/.certificado_digital/chave-privada \n"
    path_chave_privada = gets.chomp.to_s
    path_chave_privada = "#{Dir.home}/.certificado_digital/chave-privada" if path_chave_privada.empty?

    if File.exists?(path_chave_privada)
      chave_privada = File.open(path_chave_privada)
      self.chave_privada = chave_privada.read()
    else
      puts "ERRO: CHAVE PRIVADA NÃO ENCONTRADA"
      exit()
    end
  end
  def validar_certificado_digital
    chave_publica = RbNaCl::VerifyKey.new(self.chave_publica)
    validade = chave_publica.verify(self.hash_cifrado, self.hash)

    puts validade ? "Assinatura Valida" : "ASSINATURA INVÁLIDA"
  end
  def atualizar_credenciais
    puts "Informe seu nome"
    nome = gets.chomp.to_s

    puts "Informe seu e-mail"
    email = gets.chomp.to_s

    self.credenciais.concat([{ name: nome, email: email}])
  end
end

# Metodos auxiliares
def criar_novo_certificado
  puts "Informe seu nome"
  nome = gets.chomp.to_s

  puts "Informe seu e-mail"
  email = gets.chomp.to_s

  credenciais = [{ name: nome, email: email}]

  certificado_digital = CertificadoDigital.new(credenciais)
  certificado_digital.assinar_com_nova_chave()
  certificado_digital.criar_arquivo_com_chave_privada()
  certificado_digital.gerar_base64()
  json_do_certificado = certificado_digital.gerar_json()
  certificado_digital.criar_arquivo_com_certificado_digital(json_do_certificado)
end
def assinar_certificado_com_nova_chave
  certificado_digital = CertificadoDigital.new
  dados_do_certificado = certificado_digital.abrir_certificado_digital()
  certificado_digital.analisar_json(dados_do_certificado)
  certificado_digital.analisar_base64()
  certificado_digital.atualizar_credenciais()
  certificado_digital.assinar_com_nova_chave()
  certificado_digital.criar_arquivo_com_chave_privada()
  certificado_digital.gerar_base64()
  json_do_certificado = certificado_digital.gerar_json()
  certificado_digital.atualizar_certificado_digital(json_do_certificado)
end
def assinar_certificado_com_chave_existente
  certificado_digital = CertificadoDigital.new
  dados_do_certificado = certificado_digital.abrir_certificado_digital()
  certificado_digital.analisar_json(dados_do_certificado)
  certificado_digital.analisar_base64()
  certificado_digital.atualizar_credenciais()
  certificado_digital.abrir_chave_privada()
  certificado_digital.assinar_com_chave_existente()
  certificado_digital.gerar_base64()
  json_do_certificado = certificado_digital.gerar_json()
  certificado_digital.atualizar_certificado_digital(json_do_certificado)
end
def validar_certificado
  certificado_digital = CertificadoDigital.new
  dados_do_certificado = certificado_digital.abrir_certificado_digital()
  certificado_digital.analisar_json(dados_do_certificado)
  certificado_digital.analisar_base64()
  certificado_digital.validar_certificado_digital()
end

puts "Escolha a opção desejada"
puts "1) Criar novo certificado digital"
puts "2) Assinar certificado pré-existente com uma nova chave"
puts "3) Assinar certificado pré-existente com uma chave existente"
puts "4) Validar certificado digital"
opcao = gets.chomp.to_i

case opcao
  when 1 then criar_novo_certificado()
  when 2 then assinar_certificado_com_nova_chave()
  when 3 then assinar_certificado_com_chave_existente()
  when 4 then validar_certificado()
  else puts "Opção invalida"
end
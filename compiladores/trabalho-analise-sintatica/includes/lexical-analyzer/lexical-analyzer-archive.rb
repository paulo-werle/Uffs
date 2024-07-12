# frozen_string_literal: true

class LexicalAnalyzerArchive
  # Inicia parametros da classe
  def initialize(path)
    @path = path
    @lines = []
  end

  # Faz o processamento do arquivo
  def call
    file_read
    file_data
  rescue StandardError => e
    puts "Archive-Error: #{e}"
    exit(1)
  end

  private

  # Abre o arquivo
  def file
    @file ||= File.open(@path, 'r')
  end

  # Fecha o arquivo
  def close_file
    @file.close
  end

  # Le cada linha do arquivo
  def file_read
    file.each_line do |line|
      @lines << line
    end

    close_file
  end

  # Faz manipulação das informações do arquivo
  def file_data
    @lines.map(&:chars)
  end
end

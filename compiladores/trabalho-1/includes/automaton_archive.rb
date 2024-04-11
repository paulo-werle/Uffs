# frozen_string_literal: true

class AutomatonArchive
  # Inicia parametros da classe
  def initialize(path)
    @path = path

    @data = { tokens: [], grammars: [] }
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
      @lines << line.gsub("\n", '')
    end

    close_file
  end

  # Faz manipulação das informações do arquivo
  def file_data
    @separator = @lines.find_index(&:empty?)

    @data[:tokens]   = tokens
    @data[:grammars] = grammars

    @data
  end

  # Pega tokens
  def tokens
    @tokens ||= @lines[..(@separator - 1)]
  end

  # Pega gramaticas
  def grammars
    @grammars ||= @lines[(@separator + 1)..]

    @grammars
      .join("\n")
      .split(/(?=^S::=)/)
      .map { |grammar| grammar.split("\n") }
  end
end

# frozen_string_literal: true

require 'terminal-table'

class LexicalMatrix
  def initialize(data)
    @data = data
  end

  def call
    print_matrix
    print_fita
  end

  private

  def print_matrix
    table = Terminal::Table.new(
      title: 'Tabela de simbolos',
      headings: ['Estado', 'Linha', 'Indice Simbolo', 'Label'],
      rows: simbol_table_values
    )
    table.style = {
      alignment: :center
    }
    puts table
  end

  def print_fita
    print "Fita: #{@data[:fita].join(' ')}\n"
  end

  def simbol_table_values
    @data[:simbol_table].map(&:values)
  end
end

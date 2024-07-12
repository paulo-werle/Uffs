# frozen_string_literal: true

require 'terminal-table'

class Matrix
  def initialize(title, data)
    @title = title
    @data = data
  end

  def call
    matrix_initialize
    matrix_fill_rows
    matrix_fill_values
    matrix_print
  end

  private

  def matrix_initialize
    max_row = rows.size || 0
    max_col = cols.size || 0

    @matrix = Array.new(max_row) { Array.new(max_col) { '-' } }
  end

  def matrix_fill_rows
    rows.each do |row|
      @matrix[row][1] = row
    end
  end

  def matrix_fill_values
    @matrix[0][0] = '->'

    mappings.each do |mapping|
      row = mapping[:row]
      value = mapping[:value]
      col = get_col(mapping[:col])

      if col.nil? || value.nil?
        @matrix[row][0] = '*'
        next
      end

      if @matrix[row][col] == '-'
        @matrix[row][col] = value
        next
      end

      if @matrix[row][col].is_a?(Integer)
        @matrix[row][col] = [@matrix[row][col], value]
        next
      end

      @matrix[row][col] = [*@matrix[row][col], value]
    end
  end

  def matrix_print
    table = Terminal::Table.new(
      title: @title,
      headings: cols,
      rows: @matrix
    )
    table.style = {
      # width: 100,
      alignment: :center
    }
    puts table
  end

  def mappings
    @data[:mappings]
  end

  def rows
    @data[:rows]
  end

  def cols
    ['Op.', 'Simb.', *@data[:cols]]
  end

  def get_col(col)
    return if col.nil?

    col + 2
  end
end

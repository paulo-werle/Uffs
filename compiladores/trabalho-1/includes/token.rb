# frozen_string_literal: true

class Token
  # Mapeamento de colunas
  def self.cols(data)
    data[:tokens].flat_map(&:chars)
  end

  # Mapeamento de linhas
  def self.rows(data, ci = 0)
    rows = {}

    data[:tokens].each do |token|
      rows[token] = "#{token}£".chars.map.with_index do |_char, index|
        index.zero? ? 0 : (ci += 1)
      end
    end

    { rows:, ci: }
  end

  # Mapeamento de linhas e colunas
  def self.mappings(data, cols, rows)
    data[:tokens].flat_map do |token|
      "#{token}£".chars.flat_map.with_index do |char, index|
        {
          col: cols.find_index(char),
          row: rows[token][index],
          value: rows[token][index + 1]
        }
      end
    end
  end
end

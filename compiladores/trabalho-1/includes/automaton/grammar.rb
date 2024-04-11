# frozen_string_literal: true

class Grammar
  # Mapeamento de colunas
  def self.cols(data)
    data[:grammars].flat_map do |grammar|
      grammar.flat_map do |line|
        line
          .split('::=')[1]
          .split('|')
          .flat_map { |content| content.scan(/[a-z0-9]/) }
      end
    end
  end

  # Mapeamento de linhas
  def self.rows(data, ci = 0)
    rows = {}

    data[:grammars].each do |grammar|
      rows[grammar] = grammar.map.with_index do |_line, index|
        index.zero? ? 0 : (ci += 1)
      end
    end

    { rows:, ci: }
  end

  # Mapeamento de linhas e colunas
  def self.mappings(data, cols, rows)
    data[:grammars].flat_map do |grammar|
      grammar.flat_map.with_index do |line, index|
        key, rules = line.split('::=')

        rules.split('|').flat_map do |rule|
          {
            col: cols.find_index(rule[0]),
            row: rows[grammar][index],
            value: mapping_value(rule, key, rule[1], rows, grammar, index)
          }
        end
      end
    end
  end

  def self.mapping_value(rule, line_key, rule_key, rows, grammar, index)
    return if rule == '£'

    line_key == rule_key ? rows[grammar][index] : rows[grammar][index + 1]
  end
end

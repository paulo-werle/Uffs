# frozen_string_literal: true

require_relative 'token'
require_relative 'grammar'

class NonDeterministicAutomaton
  def initialize(data)
    @data = data
    @values = nil
    @states = {
      cols:     nil,
      rows:     nil,
      mappings: nil
    }

    @ci = 0
  end

  def call
    handle_values
  end

  private

  # Compactação dos estados para os valores
  def handle_values
    @values = {
      cols:       value_by_cols,
      rows:       value_by_rows,
      mappings:   value_by_mappings,
      end_states: value_by_end_states
    }
  end

  # Compactação das colunas (Caso necessario)
  def value_by_cols
    cols
  end

  # Compactação das linhas (Caso necessario)
  def value_by_rows
    rows.values.flatten.sort.uniq
  end

  # Compactação dos mapeamentos (Caso necessario)
  def value_by_mappings
    mappings
  end

  # Compactação dos estados finais
  def value_by_end_states
    states = {}

    rows.each do |key, row|
      states[key] = row.last
    end

    states
  end

  # Colunas
  def cols
    return @states[:cols] if @states[:cols]

    @states[:cols] = [*token_cols, *grammar_cols].uniq
  end

  # Colunas dos tokens
  def token_cols
    Token.cols(@data)
  end

  # Colunas das gramaticas
  def grammar_cols
    Grammar.cols(@data)
  end

  # Linhas
  def rows
    return @states[:rows] if @states[:rows]

    @states[:rows] = { **token_rows, **grammar_rows }
  end

  # Linhas dos tokens
  def token_rows
    rows, @ci = Token.rows(@data, @ci).values_at(:rows, :ci)

    rows
  end

  # Linhas das gramaticas
  def grammar_rows
    rows, @ci = Grammar.rows(@data, @ci).values_at(:rows, :ci)

    rows
  end

  # Mapeamentos
  def mappings
    return @states[:mappings] if @states[:mappings]

    @states[:mappings] = [*token_mappings, *grammar_mappings]
  end

  # Mapeamentos dos tokens
  def token_mappings
    Token.mappings(@data, cols, rows)
  end

  # Mapeamentos das gramaticas
  def grammar_mappings
    Grammar.mappings(@data, cols, rows)
  end
end

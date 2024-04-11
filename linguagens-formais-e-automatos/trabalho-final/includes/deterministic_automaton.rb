# frozen_string_literal: true

class DeterministicAutomaton
  def initialize(nda_data)
    @nda_data = nda_data

    @ci = nil
  end

  def call
    handle_values
    @values = compact_nda_mappings
  end

  private

  def handle_values
    @values = {
      # cols:       value_by_cols,
      # rows:       value_by_rows,
      mappings:   value_by_mappings
      # end_states: value_by_end_states
    }
  end

  def compact_nda_mappings
    new_mapping = {}

    nda_mappings.each do |mapping|
      value = mapping[:value]
      row = mapping[:row]
      col = mapping[:col]

      key = [
        mapping[:row],
        mapping[:col]
      ]

      if value.nil?
        new_mapping[[row, value]] = { row:, col: nil, value: nil }
        next
      end

      if new_mapping[key].nil?
        new_mapping[key] = { row:, col:, value: }
        next
      end

      new_mapping[key][:value] = [
        new_mapping[key][:value],
        value
      ]
    end

    new_mapping.values
  end

  def value_by_mappings
    @ci = nda_rows.size
    states = compact_nda_mappings.select { |dado| dado[:row].zero? }

    binding.pry
    states.each do |state|
      if state[:value].is_a?(Array)

      end
    end

    # compact_nda_mappings do |nda_mapping|

    # end
  end

  # # Método para filtrar os dados com row == 0
  # def filtrar_por_row_zero(dados)
  #   dados.select { |dado| dado[:row] == 0 }
  # end

  # # Método para encontrar as ocorrências baseadas nos valores dos dados
  # def encontrar_ocorrencias(dados, valor)
  #   dados.select { |dado| dado[:row] == valor }
  # end

  # # Método para processar os dados e encontrar as ocorrências mencionadas
  # def processar(dados)
  #   # Armazenar os dados com row == 0
  #   states = filtrar_por_row_zero(dados)

  #   # Processar os dados armazenados
  #   states.each do |state|
  #     # Verificar se o valor é um array
  #     if state[:value].is_a?(Array)
  #       # Para cada elemento no array, encontrar as ocorrências correspondentes
  #       state[:value].each do |val|
  #         state[:ocorrencias] ||= []
  #         state[:ocorrencias] += encontrar_ocorrencias(dados, val)
  #       end
  #     else
  #       # Caso contrário, encontrar as ocorrências correspondentes diretamente
  #       state[:ocorrencias] = encontrar_ocorrencias(dados, state[:value])
  #     end
  #   end

  #   # Retornar os dados processados
  #   binding.pry
  #   states
  # end

  def nda_mappings
    @nda_data[:mappings]
  end

  def nda_rows
    @nda_data[:rows]
  end
end

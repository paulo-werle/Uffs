# frozen_string_literal: true

class DeterministicAutomaton
  def initialize(data)
    @data = data
    @values = nil

    @ci = 0
  end

  def call
    handle_values
  end

  private

  def handle_values
    @values = {
      cols:       @data[:cols],
      rows:       values_by_rows,
      end_states: @data[:end_states],
      mappings:   value_by_mappings
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
    return @new_mappings.values if @new_mappings

    @ci = nda_rows.size
    @new_mappings = {}

    # Pega mapeamentos com estado inicial
    @initial_values = compact_nda_mappings.select do |nda_mapping|
      nda_mapping[:row].zero?
    end

    @initial_values.each do |mapping|
      next mapping_value(mapping) unless mapping[:value].is_a?(Array)

      mapping_array_value(mapping)
      @ci += 1
    end

    @new_mappings.values
  end

  def mapping_array_value(mapping)
    row = mapping[:row]
    col = mapping[:col]

    # Adiciona novo mapping
    @new_mappings[[row, col]] = { row:, col:, value: @ci }

    # Busca por linhas citadas que ainda não foram mapeadas
    values = compact_nda_mappings.select do |nda|
      mapping[:value].include?(nda[:row]) &&
        @new_mappings[[nda[:row], nda[:col]]].nil?
    end

    # Adiciona os valores para a busca e para o mapeamento atual
    values.each do |val|
      new_mapping = {
        row:   @ci,
        col:   val[:col],
        value: val[:value]
      }

      @new_mappings[[@ci, val[:col]]] = new_mapping
      @initial_values << new_mapping
    end
  end

  def mapping_value(mapping)
    row = mapping[:row]
    col = mapping[:col]

    # Adiciona novo mapping
    @new_mappings[[row, col]] = mapping

    # Busca por linhas citadas que ainda não foram mapeadas
    values = compact_nda_mappings.select do |nda|
      mapping[:value] == nda[:row] &&
        @new_mappings[[nda[:row], nda[:col]]].nil?
    end

    # Adiciona os valores para a busca e para o mapeamento atual
    values.each do |val|
      @new_mappings[[val[:row], val[:col]]] = val
      @initial_values << val
    end
  end

  def values_by_rows
    rows = value_by_mappings.map { |mapping| mapping[:row] }

    [*nda_rows, *rows].sort.uniq
  end

  def nda_mappings
    @data[:mappings]
  end

  def nda_rows
    @data[:rows]
  end
end

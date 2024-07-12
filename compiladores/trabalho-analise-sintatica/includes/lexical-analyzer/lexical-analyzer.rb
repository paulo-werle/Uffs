# frozen_string_literal: true

class LexicalAnalyzer
  def initialize(lexical_data, automaton_data)
    @lexical_data = lexical_data
    @automaton_data = automaton_data

    @simbol_table = []
    @fita = []
  end

  def call
    apply_syntactic_analysis

    {
      simbol_table: @simbol_table,
      fita: @fita
    }
  end

  private

  def apply_syntactic_analysis
    @automato_control = 0
    @sentence = []
    @state = nil

    @lexical_data.each_with_index do |line, line_index|
      line.each_with_index do |simbol, simbol_line|
        # Caso o simbolo seja um separador
        if simbol_is_separator?(simbol)
          record_data(line_index, simbol_line) unless final_state.nil?
          @automato_control = 0
          @sentence = []
          next
        end

        # Pega o estado no automato
        @state = automaton_value(simbol)
        @sentence << simbol

        # Verifica se é um estado valido
        if @state.nil?
          record_error(line_index, simbol_line)
          @automato_control = 0
          next
        end

        @automato_control = @state[:value]
      end
    end
  end

  def record_data(line, simbol)
    @simbol_table << {
      state: @state[:value],
      line: line + 1,
      simbol: simbol + 1,
      label: @sentence
    }
    @fita << @state[:value]
  end

  def record_error(line, simbol)
    @simbol_table << {
      state: '!',
      line: line + 1,
      simbol: simbol + 1,
      label: @sentence
    }
    @fita << '!'
  end

  def simbol_is_separator?(simbol)
    [' ', "\n"].include?(simbol)
  end

  def final_state
    row = @automato_control
    value = nil
    col = nil

    mappings.find do |mapping|
      mapping[:row] == row && mapping[:col] == col && mapping[:value] == value
    end
  end

  def automaton_value(simbol)
    row = @automato_control
    col = cols.find_index(simbol)
    return unless col

    mappings.find do |mapping|
      mapping[:row] == row && mapping[:col] == col
    end
  end

  def cols
    @automaton_data[:cols]
  end

  def mappings
    @automaton_data[:mappings]
  end
end

# frozen_string_literal: true

# Importações de bibliotecas
require 'pry'

# Importações relacionadas ao automato
require './includes/automaton/matrix'
require './includes/automaton/automaton_archive'
require './includes/automaton/deterministic_automaton'
require './includes/automaton/non_deterministic_automaton'

# Importações relacionadas ao analisador lexico
require './includes/lexical_analyzer/lexical_analyzer'
require './includes/lexical_analyzer/lexical_analyzer_archive'

# Abre arquivo
automaton_archive = AutomatonArchive.new("#{Dir.pwd}/inputs/automaton/input.txt")
automaton_archive_data = automaton_archive.call
# print automaton_archive_data

# Execução do automato indeterministico
nda = NonDeterministicAutomaton.new(automaton_archive_data)
nda_data = nda.call
# print nda_mappings

# Cria matriz para impressão
nda_matrix = Matrix.new('Automato Finito Indeterministico', nda_data)
nda_matrix.call

# Execução do automato deterministico
da = DeterministicAutomaton.new(nda_data)
da_data = da.call
# print da_mappings

# Cria matriz para impressão
nda_matrix = Matrix.new('Automato Finito Deterministico', da_data)
nda_matrix.call

# Abre o arquivo para analise lexica
lexical_archive = LexicalAnalyzerArchive.new("#{Dir.pwd}/inputs/lexical_analyzer/input.txt")
lexical_archive_data = lexical_archive.call

# Execução do analisador lexico
lexical_analyzer = LexicalAnalyzer.new(lexical_archive_data, da_data)
lexical_analyzer_data = lexical_analyzer.call
binding.pry

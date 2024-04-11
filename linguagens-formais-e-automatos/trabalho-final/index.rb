# frozen_string_literal: true

# Importações
require 'pry'
require './includes/matrix'
require './includes/archive'
require './includes/deterministic_automaton'
require './includes/non_deterministic_automaton'

# Abre arquivo
archive = Archive.new("#{Dir.pwd}/input#{ARGV[0] ? "_#{ARGV[0]}" : ''}.txt")
archive_data = archive.call
# print archive_data

# Execução do automato indeterministico
nda = NonDeterministicAutomaton.new(archive_data)
nda_data = nda.call
# print nda_mappings

# Cria matriz para impressão
nda_matrix = Matrix.new(nda_data)
nda_matrix.call

# Execução do automato deterministico
da = DeterministicAutomaton.new(nda_data)
da.call
# print da_mappings

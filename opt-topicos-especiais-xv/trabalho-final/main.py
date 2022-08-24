# # ------ Bibliotecas ------
from sys       import maxsize
from time      import time

# # ------ Arquivos ------
from includes.files              import readFiles
from includes.files              import writeFile
from includes.helpers            import calculateTime
from includes.helpers            import mountInstanceOutput
from includes.searchConstructive import constructiveSearch
from includes.searchLocal        import localSearch

# ------ Funções ------

# Função para controlar execuções
def controlExecutions(instance):
  solution = { 'cost': maxsize }
  sTime = time()

  # Executa enquanto tiver tempo
  while (time() - sTime) <= instance['time']:
    currentSolution = localSearch(
      constructiveSearch(instance), instance
    )

    # Caso a solução gerada for melhor do que a atual
    if currentSolution['cost'] < solution['cost']:
      solution = currentSolution

  # Marcando tempo de execução
  solution['time'] = time() - sTime
  return solution

# Função para lidar com as buscas
def handleSearches(instance):
  instance['time'] = calculateTime(instance)
  tSolutions = []
  solutions = []

  # Executa a busca 10 vezes
  for index in range(10):
    solutions.append( controlExecutions(instance) )
    print(index, instance['name'], '- encerrou execução')

  return solutions

# ------ Programa ------
fileNames = ['Djibouti', 'Qatar', 'Uruguay', 'Western Sahara', 'Zimbabwe']
outputs = []

# Faz a leitura dos dados do arquivo
instaceList = readFiles(fileNames)

# Percorre cada instancia
for instance in instaceList:

  # Faz as buscas
  instance['solutions'] = handleSearches(instance)

  # Monta saida da instancia
  outputs.append( mountInstanceOutput(instance) )

# Escreve resultados no arquivo
writeFile(outputs)


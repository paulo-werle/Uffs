import statistics
import random
import time
import csv
import sys

# ------ Funções ------
# Função para ler instancias
def readPreparedInstances(fileNames):
  instanceList = []

  # Percorre cada arquivo
  for fileName in fileNames:
    with open( f"./prepared-instances/{fileName}.csv", 'r' ) as file:
      instance = []
      lines = csv.reader(file)

      # Percorre linhas do arquivo armazenando em um array
      for line in lines:
        instance.append(line)

    instanceList.append({
      'name': fileName,
      'content': instance
    })

  return instanceList

# Função para avaliar o caminho
def evaluatePath(pathStructure, instance):
  path = pathStructure['path']
  matrix = instance['content']
  lIndex = path[-1]
  result = []

  # Buscar valor do caminho
  for index in path:
    result.append(int( matrix[lIndex][index] ))
    lIndex = index

  return {
    'path': pathStructure['path'],
    'ids': pathStructure['ids'],
    'cost': sum(result)
  }

# Função para gerar caminho inicial
def generateInitialPath(instance):
  size = len(instance['content'])
  intialStructure = { 'path': random.sample(range(size), size), 'ids': [] }

  return evaluatePath(intialStructure, instance)

# Função para calcular tempos
def calculateTime(instance):
  size = len(instance['content'])

  # Regra de 3 para calcular tempo proporcional
  return (size * 60) / 1000

# Função para calcular mandato
def calculateMandate(instance):
  size = len(instance['content'])

  return round(size / 5)

# Função para alterar com 2OP2
def handle2Opt(pathStructure, xId, yId):
  minId, maxId = sorted([xId, yId])
  path = pathStructure['path']

  generatedPath = [
    *path[:minId],
    *reversed(path[minId:maxId]),
    *path[maxId:]
  ]

  return { 'path': generatedPath, 'ids': [minId, maxId] }

# Função para comparar melhor caminho
def comparePaths(current, best):
  return current if current['cost'] <= best['cost'] else best

# Função para lidar com tabus
def handleTaboo(tabooStructure, currentStructure):
  for taboo in tabooStructure:
    # Verefica se deve remover tabu
    if taboo['mandate'] == instance['mandate']:
      tabooStructure.remove(taboo)

    # Contador do mandato
    taboo['mandate'] = taboo['mandate'] + 1

  # Adiciona tabu
  tabooStructure.append({ 'ids': currentStructure['ids'], 'mandate': 0 })

# Função para verefica se é tabu
def isTaboo(tabooStructure, pathStructure):
  # Monta um array com os tabus ids
  tabooIds = map(lambda taboo: taboo['ids'], tabooStructure)

  return sorted(pathStructure['ids']) in tabooIds

# Função para buscar melhor solução
def handleSortingSolutions(solutions, pathStructure, tabooStructure):
  sortedSolutions = sorted( solutions, key = lambda solution: solution['cost'] )

  # Considera se o elemento não é tabu, ou se passa no criterio de aspiração
  for solution in sortedSolutions:
    if not isTaboo(tabooStructure, solution) or solution['cost'] < pathStructure['cost']:
      return solution

# Função para gerar os paths
def generatePaths(instance, pathStructure, sTime, tabooStructure):
  generatedSolutions = []
  size = len(instance['content'])
  currentBestPath = pathStructure

  for xId in range(size):
    for yId in range(size):
      if xId != yId:
        # Combinar como 2OPT
        generatedPath = handle2Opt(currentBestPath, xId, yId)
        # Avalia caminho gerado
        evaluatedPath = evaluatePath(generatedPath, instance)
        # Adiciona caminho gerado nas soluções
        generatedSolutions.append(evaluatedPath)

      # Condição de parada por tempo
      if (time.time() - sTime) >= instance['time']:
        break

  # Seleciona melhor elemento não considerando tabus, mas com criterio des apiração
  currentBestPath = handleSortingSolutions(generatedSolutions, pathStructure, tabooStructure)

  return currentBestPath

# Função para manipular as informações da busca local
def handleLocalSearch(instance):
  currentStructure = generateInitialPath(instance)
  tabooStructure = []
  sTime = time.time()

  while True:
    # Gera vizinhança do caminho
    generatedStructure = generatePaths(instance, currentStructure, sTime, tabooStructure)
    # Compara solução gerada com a atual
    currentStructure = comparePaths(currentStructure, generatedStructure)
    # Função para lidar com os tabus
    handleTaboo(tabooStructure, currentStructure)

    # Condição de parada por tempo
    if (time.time() - sTime) >= instance['time']:
      break

  # Marca tempo de execução
  currentStructure['time'] = time.time() - sTime

  return currentStructure

# Função do algoritmo de busca local
def localSearch(instance):
  solutions = []

  # Gerar tempos de execução
  instance['time'] = calculateTime(instance)

  # Gerar tamanho do mandato
  instance['mandate'] = calculateMandate(instance)

  # Faz as 10 buscas locais
  for index in range(10):
    solutions.append( handleLocalSearch(instance) )
    print(index, instance['name'], '- encerrou execução')

  return solutions

# Função para montar a saida da instancia
def mountInstanceOutput(instance):
  costValues = []
  timeValues = []

  for solution in instance['solutions']:
    costValues.append(solution['cost'])
    timeValues.append(solution['time'])

  return [
    instance['name'],
    'Paulo.Werle',
    'BT2opt',
    round(statistics.mean(costValues)),
    round(statistics.stdev(costValues), 2),
    round(statistics.mean(timeValues))
  ]

# Função para escrever a saida
def writeOutput(outputs):

  # Monta arquivo no formato escrita
  with open( f"./resultados.csv", 'w' ) as file:
    writer = csv.writer(file)

    # Escreve cabeçalho
    writer.writerow([
      'instancia',
      'autoria',
      'algoritmo',
      'q-medio',
      'q-desvio',
      't-medio'
    ])

    # Percorre saidas para escrever no arquivo
    for output in outputs:
      writer.writerow(output)

# ------ Programa ------
fileNames = ['Djibouti', 'Qatar', 'Uruguay', 'Western Sahara', 'Zimbabwe']
outputs = []

# Faz a leitura dos dados do arquivo
instaceList = readPreparedInstances(fileNames)

# Percorre cada instancia
for instance in instaceList:

  # Executa algoritmo de busca local
  instance['solutions'] = localSearch(instance)

  # Monta saida
  instanceOutput = mountInstanceOutput(instance)

  # Adiciona saida da instancia as saidas
  outputs.append(instanceOutput)

# Escreve saidas no arquivo
writeOutput(outputs)
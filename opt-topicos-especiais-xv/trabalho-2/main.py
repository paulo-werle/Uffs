import statistics
import random
import math
import time
import sys

# ------ Variaveis ------
# Utilizado para definir configurações dos algoritmos
# - Caso valor for 'None' pega valor default do algoritmo
randomAlgorithmTime = 0.2
randomAlgorithmLen = 20

bruteForceAlgorithmSize = None

# ------ Funções ------
# Função para ler instancias
def readInstances(fileNames):
  # Inicia lista de instancias
  instanceList = []

  # Percorre cada arquivo
  for fileName in fileNames:
    with open( f"../Instances/{fileName}.tsp", 'r' ) as file:
      instance = []
      lines = file.read().splitlines()

      # Define conteudo
      content = lines[(lines.index('NODE_COORD_SECTION') + 1):lines.index('EOF')]

      # Percorre cada linha do conteudo
      for line in content:
        values = line.split(' ')

        # Adiciona o conteudo na instancia
        instance.append({
          'index': int(values[0]),
          'xCoordinate': float(values[1]),
          'yCoordinate': float(values[2])
        })

    # Adiciona instancia na lista
    instanceList.append({
      'name': fileName,
      'content': instance
    })

  return instanceList

# Função para calcular a Distância euclidiana
def calculateEuclideanDistance(point1, point2):
  # Executa a seguinte operação: SQRT((x1-x2)^2+(y1-y2)^2)
  xValue = (point1['xCoordinate'] - point2['xCoordinate']) ** 2
  yValue = (point1['yCoordinate'] - point2['yCoordinate']) ** 2

  value = math.sqrt(xValue + yValue)

  return round(value)

# Função para criar matrix de adjacência
def createAdjacencyMatrix(instance):
  matrix = []

  # Percorre linhas do conteudo
  for xLine in instance['content']:
    array = []

    # Percorre linhas do conteudo
    for yLine in instance['content']:

      # Calcula a distancia de cada linhaX para cada linhaY
      array.append(
        calculateEuclideanDistance(xLine, yLine)
      )

    matrix.append(array)

  return matrix

# Função principal do algoritmo aleatorio
def randomAlgorithm(adjacencyMatrix):

  # Começa a medir o tempo de execução
  startTime = time.time()

  # Gerar caminhos para o algoritmo
  paths = generatePathsByRandomAlgorithm(adjacencyMatrix)

  # Encontrar custo de cada caminho
  analyzedPaths = analyzePaths(paths, adjacencyMatrix)

  # Monta saida do algoritmo
  assembleAlgorithmOutput(analyzedPaths, startTime, 'ALEATÓRIO')

# Função principal do algoritmo força bruta
def bruteForceAlgorithm(adjacencyMatrix):

  # Começa a medir o tempo de execução
  startTime = time.time()

  # Gerar caminhos para o algoritmo
  paths = generatePathsByBruteForceAlgorithm(adjacencyMatrix)

  # Encontrar custo de cada caminho
  analyzedPaths = analyzePaths(paths, adjacencyMatrix)

  # Monta saida do algoritmo
  assembleAlgorithmOutput(analyzedPaths, startTime, 'FORÇA BRUTA')

# Função para gerar caminhos pelo Algoritmo aleatorio
def generatePathsByRandomAlgorithm(adjacencyMatrix):
  pathsLen = randomAlgorithmLen or 1000
  maxTime = randomAlgorithmTime or 30

  matrixSize = len(adjacencyMatrix)
  paths = []

  # Começa a contar o tempo
  startTime = time.time()

  # Percorre enquanto tiver tempo
  while time.time() - startTime <= maxTime and len(paths) <= pathsLen:
    paths.append(random.sample(range(matrixSize), matrixSize))

  # Retorna caminhos gerados
  return paths

# Função para gerar caminhos pelo Algoritmo força bruta
def generatePathsByBruteForceAlgorithm(adjacencyMatrix):
  matrixSize = bruteForceAlgorithmSize or len(adjacencyMatrix)
  paths = []

  def recursiveFunction(indexes, index):
    # Remove indice da lista
    indexes.remove(index)
    path = []

    # Caso a lista não tiver mais indices
    if not indexes:
      return index

    # Percorre indices da lista
    for index in indexes:

      # Cria uma copia da lista
      handleIndexes = indexes.copy()

      # Chama função recursiva com as opções possiveis de indices
      results = recursiveFunction(handleIndexes, index)

      # Caso o results for um array, inclui ele e o indice em cada resultado
      if isinstance(results, list):
        for result in results:
          path.append([index, *result])

      # Caso o results não for um array, inclui ele no resultado
      else:
        path.append([results])

    # Retorna o caminho encontrado até o momento
    return path

  # Cria um array de indices
  indexes = list(range(1, matrixSize))

  # Percorre indices da lista
  for index in indexes:

    # Cria uma copia da lista
    handleIndexes = indexes.copy()

    # Chama função recursiva com as opções possiveis de indices
    results = recursiveFunction(handleIndexes, index)

    for result in results:
      paths.append([0, index, *result])

  # Retorna caminhos gerados
  return paths

# Função para analisar o caminho
def analyzePaths(paths, adjacencyMatrix):
  solutions = []

  # Percorre cada caminho
  for path in paths:
    lastIndex = path[-1]
    result = []

    # Percorre cada parte do caminho para encontrar custo
    for currentIndex in path:
      result.append(adjacencyMatrix[lastIndex][currentIndex])
      lastIndex = currentIndex

    solutions.append({
      'path': path,
      'cost': sum(result)
    })

  return solutions

# Funçaõ para montar a saida dos Algoritmos
def assembleAlgorithmOutput(solutions, startTime, algorithmName):
  bestSolution = {'cost': sys.maxsize }
  costs = []

  for solution in solutions:

    # Adiciona custo no array de custos
    costs.append(solution['cost'])

    # Caso custo da solução for menor que a da melhor solução
    if bestSolution['cost'] > solution['cost']:
      bestSolution = solution

  # Calcula tempo total de execução
  totalTime = time.time() - startTime

  print(
    'Melhor custo: {}, Melhor caminho: {}, Média de custos: {}, Tempo de execução: {:.9f}, Algoritmo: {}'.format(
    bestSolution['cost'],
    bestSolution['path'],
    int(statistics.mean(costs)),
    totalTime,
    algorithmName
    )
  )


# ------ Programa ------
# Configurações do programa
fileNames = ['Western-Sahara']

# Faz a leitura dos dados do arquivo
instaceList = readInstances(fileNames)

# Percorre cada instancia
for instance in instaceList:

  # Cria a matrix de adjacencia (Distancia das cidades)
  instance['adjacencyMatrix'] = createAdjacencyMatrix(instance)

  # Executa algoritmo aleatorio
  randomAlgorithm(instance['adjacencyMatrix'])

  # Executa algoritmo aleatorio
  bruteForceAlgorithm(instance['adjacencyMatrix'])
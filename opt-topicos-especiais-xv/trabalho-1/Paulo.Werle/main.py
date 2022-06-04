import statistics
import random
import time
import csv
import sys

# ------ Funções ------
# Função para ler instancias
def readPreparedInstances(fileNames):

  # Inicia lista de instancias
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

# Função principal do algoritmo aleatorio
def randomAlgorithm(instance):
  solutions = []

  for _index in range(10):
    # Começa a medir o tempo de execução
    times = { 'start': time.time() }

    # Gerar tempo linear para cada instancia
    generateTime(instance)

    # Gerar caminhos para o algoritmo
    paths = generatePaths(instance)

    # Encontrar custo de cada caminho
    analyzedPaths = analyzePaths(paths, instance['content'])

    # Finaliza a medição do tempo de execução
    times['end'] = time.time()

    # Monta saida do algoritmo
    solution = mountAlgorithmReturn(analyzedPaths, times)

    # Acrecentar melhor solução da rodada as soluções
    solutions.append(solution)

  return solutions

# Função para calcular tempo maximo de cada instancia
def generateTime(instance):
  matrixSize = len(instance['content'])

  # Gerar tempo pela quantidade de pontos
  time = (matrixSize * 60) / 1000

  # Adicionar tempo no objeto da instancia
  instance['time'] = time

# Função para gerar caminhos aleatoriamente
def generatePaths(instance):
  matrixSize = len(instance['content'])
  maxTime = instance['time']
  paths = []

  # Começa a contar o tempo
  startTime = time.time()

  # Percorre enquanto tiver tempo
  while time.time() - startTime <= maxTime:
    paths.append(random.sample(range(matrixSize), matrixSize))

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
      result.append(int(adjacencyMatrix[lastIndex][currentIndex]))
      lastIndex = currentIndex

    solutions.append({
      'path': path,
      'cost': sum(result)
    })

  return solutions

# Função para montar a saida dos Algoritmos
def mountAlgorithmReturn(solutions, times):
  bestSolution = {'cost': sys.maxsize }
  costs = []

  for solution in solutions:

    # Adiciona custo no array de custos
    costs.append(solution['cost'])

    # Caso custo da solução for menor que a da melhor solução
    if bestSolution['cost'] > solution['cost']:
      bestSolution = solution

  # Calcula tempo total de execução
  totalTime = times['end'] - times['start']

  return {
    'cost': bestSolution['cost'],
    'time': totalTime
  }

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
    'BTA',
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

  # Executa algoritmo aleatorio
  instance['solutions'] = randomAlgorithm(instance)

  # Monta saida
  instanceOutput = mountInstanceOutput(instance)

  # Adiciona saida da instancia as saidas
  outputs.append(instanceOutput)

# Escreve saidas no arquivo
writeOutput(outputs)
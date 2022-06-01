import statistics
import random
import time
import math
import csv
import sys

# ------ Funções ------
# Função para ler instancias
def readInstances(fileNames):
  instanceList = []

  for fileName in fileNames:
    with open( f"../Instances/{fileName}.tsp", 'r' ) as file:
      instance = []
      lines = file.read().splitlines()
      content = lines[(lines.index('NODE_COORD_SECTION') + 1):lines.index('EOF')]

      for line in content:
        values = line.split(' ')

        instance.append({
          'index': int(values[0]),
          'xCoordinate': float(values[1]),
          'yCoordinate': float(values[2])
        })

    instanceList.append({
      'name': fileName,
      'content': instance
    })

  return instanceList

# Função para escrever instancias
def writeInstances(instaceList):
  for instace in instaceList:
    with open( f"../Prepared-Instances/{instace['name']}.csv", 'w' ) as file:
      for line in instace['adjacencyMatrix']:
        writer = csv.writer(file)
        writer.writerow(line)

# Função para calcular a Distância euclidiana
def calculateEuclideanDistance(point1, point2):
  # SQRT((x1-x2)^2+(y1-y2)^2)
  xValue = (point1['xCoordinate'] - point2['xCoordinate']) ** 2
  yValue = (point1['yCoordinate'] - point2['yCoordinate']) ** 2

  value = math.sqrt(xValue + yValue)

  return round(value)

# Função para criar matrix de adjacência
def createAdjacencyMatrix(instance):
  matrix = []

  for xLine in instance['content']:
    array = []
    for yLine in instance['content']:
      array.append(
        calculateEuclideanDistance(xLine, yLine)
      )

    matrix.append(array)

  return matrix

# Função para gerar solução aleatoria
def randomSolution(matrix, size, bestSolution):
  order = random.sample(range(0, size), size)
  previous = order[-1]
  solution = []

  for current in order:
    solution.append(matrix[previous][current])
    previous = current

  cost = sum(solution)
  if bestSolution['cost'] > cost:
    bestSolution['cost'] = cost
    bestSolution['way'] = solution

  return bestSolution

# Função do algoritmo de soluções aleatorias
def randomSolutionAlgorithm(matrix):
  result = {'way': [], 'cost': sys.maxsize, 'average': sys.maxsize }
  size = len(matrix)
  solutions = []
  costs = []

  for _index in range(10):
    initialTime = time.time()
    solution = {'way': [], 'cost': sys.maxsize }

    while ((time.time() - initialTime) <= 30):
      solution = randomSolution(matrix, size, solution)

    solutions.append(solution)

  for solution in solutions:
    costs.append(solution['cost'])

    if result['cost'] > solution['cost']:
      result = solution

  result['average'] = statistics.mean(costs)
  return result

# ------ Programa ------
# Define nome dos arquivos usados
fileNames = ['Western-Sahara']
# Le arquivos
instaceList = readInstances(fileNames)
# Percorre instancias
for instance in instaceList:
  # Cria matriz de ajacencia
  instance['adjacencyMatrix'] = createAdjacencyMatrix(instance)
  # Usa solução do algoritmo aleatorio
  resultRandom = randomSolutionAlgorithm(instance['adjacencyMatrix'])
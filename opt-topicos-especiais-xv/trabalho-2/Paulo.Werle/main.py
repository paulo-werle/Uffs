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
def localSearch(instance):
  solutions = []

  # Gerar tempo linear para cada instancia
  generateTime(instance)

  # Achar melhor melhor com o 2OPT
  for _ in range(10):
    solutions.append(
      handlePaths(instance)
    )

  return solutions

# Função para calcular tempo maximo de cada instancia
def generateTime(instance):
  matrixSize = len(instance['content'])

  # Gerar tempo pela quantidade de pontos
  time = (matrixSize * 60) / 1000

  # Adicionar tempo no objeto da instancia
  instance['time'] = time

# Função para manipular os paths
def handlePaths(instance):
  markedTime = time.time()
  matrixSize = len(instance['content'])

  # Gera caminho aleatorio inicial
  randomPath = random.sample(range(matrixSize), matrixSize)
  solution = analyzePath(randomPath, instance)

  while True:
    # Gera soluções visinhas
    generatedSolution = generatePaths(solution, instance, markedTime)

    # Condição de parada por tempo
    if (time.time() - markedTime) >= instance['time']:
      print(instance['name'], '- foi parado pela condição de tempo')
      break

    # Condição de parada por não melhorar
    if generatedSolution['cost'] >= solution['cost']:
      print(instance['name'], '- foi parado pela condição de melhorar')
      break

    solution = generatedSolution

  # Marca tempo que finalizou
  solution['time'] = time.time() - markedTime

  return solution

# Função para gerar os paths da vizinhança
def generatePaths(solution, instance, markedTime):

  matrixSize = len(instance['content'])
  path = solution['path']

  for xIndex in range(matrixSize):
    for yIndex in range(matrixSize):

      # Condição de parada por tempo
      if (time.time() - markedTime) >= instance['time']:
        break

      if xIndex != yIndex:
        minIndex = min(xIndex, yIndex)
        maxIndex = max(xIndex, yIndex)

        # Gera caminho com o conceito do 2OPT
        generatedPath = [
          *path[:minIndex],
          *reversed(path[minIndex:maxIndex]),
          *path[maxIndex:]
        ]

        # Analisa custo do caminho gerado
        generatedSolution = analyzePath(generatedPath, instance)

        # Verefica se é melhor
        if generatedSolution['cost'] <= solution['cost']:
          solution = generatedSolution

  # Retorna a melhor melhor
  return solution

def generatePath(path, xIndex, yIndex):
  minIndex = min(xIndex, yIndex)
  maxIndex = max(xIndex, yIndex)

  generatedPath = [
    *path[:minIndex],
    *reversed(path[minIndex:maxIndex]),
    *path[maxIndex:]
  ]

  return generatedPath

# Função para analisar o caminho
def analyzePath(path, instance):

  adjacencyMatrix = instance['content']
  lastIndex = path[-1]
  result = []

  # Percorre cada parte do caminho para encontrar custo
  for currentIndex in path:
    result.append( int(adjacencyMatrix[lastIndex][currentIndex]) )
    lastIndex = currentIndex

  return {
    'path': path,
    'cost': sum(result)
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
    'BLMM2opt',
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
# import statistics
import random
import time
import csv
# import sys

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

# Função para avaliar o caminho
def evaluatePath(path, instance):

  matrix = instance['content']
  lIndex = path[-1]
  result = []

  # Buscar valor do caminho
  for index in path:
    result.append(int( matrix[lIndex][index] ))
    lIndex = index

  return { 'path': path, 'cost': sum(result) }

# Função para gerar caminho inicial
def generateInitialPath(instance):
  size = len(instance['content'])

  return evaluatePath(
    random.sample(range(size), size),
    instance
  )

# Função para gerar tempos
def calculateTime(instance):
  matrixSize = len(instance['content'])

  # Regra de 3 para calcular tempo proporcional
  return (matrixSize * 60) / 1000

# Função para gerar 2OP2
def handle2Opt(path, xId, yId):
  if xId != yId:
    minId = min(xId, yId)
    maxId = max(xId, yId)

    generatedPath = [
      *path[:minId],
      *reversed(path[minId:maxId]),
      *path[maxId:]
    ]

  return generatedPath

# Função para gerar os paths
def generatePaths(instance, current, sTime):
  size = len(instance['content'])
  path = current['path']

  for xId in range(size):
    for yId in range(size):

      # Combinar como 2OPT
      generatedPath = handle2Opt(path, xId, yId)
      print(generatedPath)

    # Condição de parada por tempo
    if (time.time() - sTime) >= instance['time']:
      break


# Função para manipular as informações da busca local
def handleLocalSearch(instance):
  sTime = time.time()

  while True:
    current = generateInitialPath(instance)

    generatePaths(instance, current, sTime)

    # Condição de parada por tempo
    if (time.time() - sTime) >= instance['time']:
      break



# Função do algoritmo de busca local
def localSearch(instance):

  # Gerar tempos de execução
  instance['time'] = calculateTime(instance)

  # Função para manipular a busca local
  handleLocalSearch(instance)



# # Função para calcular tempo maximo de cada instancia
# def generateTime(instance):
#   matrixSize = len(instance['content'])

#   # Gerar tempo pela quantidade de pontos
#   time = (matrixSize * 60) / 1000

#   # Adicionar tempo no objeto da instancia
#   instance['time'] = time

# # Função principal de busca local
# def localSearch(instance):
# #   solutions = []

#   # Gerar tempo linear para cada instancia
#   generateTime(instance)

#   # Achar melhor melhor com o 2OPT
#   handlePaths(instance)
#   # for _ in range(10):
#   #   solutions.append(
#   #   )

#   # return solutions

# # Função para manipular os paths
# def handlePaths(instance):
#   markedTime = time.time()
#   matrixSize = len(instance['content'])

# #   # Gera caminho aleatorio inicial
#   randomPath = random.sample(range(matrixSize), matrixSize)
#   solution = analyzePath(randomPath, instance)

#   while True:
#     # Gera soluções visinhas
#     generatedSolution = generatePaths(solution, instance, markedTime)

#   #   # Condição de parada por tempo
#   #   if (time.time() - markedTime) >= instance['time']:
#   #     print(instance['name'], '- foi parado pela condição de tempo')
#   #     break

#   #   # Condição de parada por não melhorar
#   #   if generatedSolution['cost'] >= solution['cost']:
#   #     print(instance['name'], '- foi parado pela condição de melhorar')
#   #     break

#   #   solution = generatedSolution

#   # # Marca tempo que finalizou
#   # solution['time'] = time.time() - markedTime

#   # return solution

# # Função para gerar os paths da vizinhança
# def generatePaths(solution, instance, markedTime):

#   matrixSize = len(instance['content'])
#   path = solution['path']

#   for xIndex in range(matrixSize):
#     for yIndex in range(matrixSize):
#       if xIndex != yIndex:
#         minIndex = min(xIndex, yIndex)
#         maxIndex = max(xIndex, yIndex)

#         # Gera caminho com o conceito do 2OPT
#         generatedPath = [
#           *path[:minIndex],
#           *reversed(path[minIndex:maxIndex]),
#           *path[maxIndex:]
#         ]

#         # Analisa custo do caminho gerado
#         generatedSolution = analyzePath(generatedPath, instance)

#         # Verefica se é melhor
#         if generatedSolution['cost'] <= solution['cost']:
#           solution = generatedSolution

#     # Condição de parada por tempo
#     if (time.time() - markedTime) >= instance['time']:
#       break

#   # # Retorna a melhor melhor
#   # return solution

# # Função para gerar vizinhança com a 2OPt
# # def generatePath(path, xIndex, yIndex):
# #   minIndex = min(xIndex, yIndex)
# #   maxIndex = max(xIndex, yIndex)

# #   generatedPath = [
# #     *path[:minIndex],
# #     *reversed(path[minIndex:maxIndex]),
# #     *path[maxIndex:]
# #   ]

# #   return generatedPath

# # Função para montar a saida da instancia
# def mountInstanceOutput(instance):
#   costValues = []
#   timeValues = []

#   for solution in instance['solutions']:
#     costValues.append(solution['cost'])
#     timeValues.append(solution['time'])

#   return [
#     instance['name'],
#     'Paulo.Werle',
#     'BT2opt',
#     round(statistics.mean(costValues)),
#     round(statistics.stdev(costValues), 2),
#     round(statistics.mean(timeValues))
#   ]

# # Função para escrever a saida
# def writeOutput(outputs):

#   # Monta arquivo no formato escrita
#   with open( f"./resultados.csv", 'w' ) as file:
#     writer = csv.writer(file)

#     # Escreve cabeçalho
#     writer.writerow([
#       'instancia',
#       'autoria',
#       'algoritmo',
#       'q-medio',
#       'q-desvio',
#       't-medio'
#     ])

#     # Percorre saidas para escrever no arquivo
#     for output in outputs:
#       writer.writerow(output)

# # ------ Programa ------
# fileNames = ['Djibouti', 'Qatar', 'Uruguay', 'Western Sahara', 'Zimbabwe']
# outputs = []
fileNames = ['Western Sahara']

# Faz a leitura dos dados do arquivo
instaceList = readPreparedInstances(fileNames)

# Percorre cada instancia
for instance in instaceList:

  # Executa algoritmo de busca local
  localSearch(instance)

#   # Monta saida
#   # instanceOutput = mountInstanceOutput(instance)

#   # Adiciona saida da instancia as saidas
#   # outputs.append(instanceOutput)

# # Escreve saidas no arquivo
# # writeOutput(outputs)
import statistics
import random
import time
import csv
import sys
import math

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

    # Define tamanho da instancia
    size = len(instance) - 1

    # Guarda informações em estrutura
    instanceList.append({
      'name': fileName,
      'matrix': instance,
      'size': size
    })

  return instanceList

# Função para calcular tempos
def calculateTime(instance):
  return (instance['size'] * 60) / 1000

# Função para calcular α
def calculateAlpha(orderedResults):
  return math.ceil(len(orderedResults) * 0.3)

# Função para gerar array inicial
def generateInitialElement(size):
  return [random.randint(0, size)]

# Função para ver quais são os elementos restantes
def remainingElements(elements, instance, size):

  # TODO - Incluido um pq o range não pega o elemento max
  allElements = set(range(size + 1))
  current = set(elements)

  return list(allElements - current)

# Função para gerar os melhores elementos
def generateBestElements(elements, remaining, instance):
  lIndex = elements[-1]
  results = []

  # Percorre restantes para saber custo
  for index in remaining:
    cost = int(instance['matrix'][lIndex][index])

    results.append({
      'index': index, 'cost': cost
    })

  # Ordena resultados pelo custo
  orderedResults = sorted(results, key = lambda result: result['cost'])

  # Calcula quantos elementos são 30%
  alpha = calculateAlpha(orderedResults)

  # Retorna os 30% melhores
  return orderedResults[:alpha]

# Função para fazer a busca heuristica
def heuristicSearch(elements, instance, size):
  # Pega elementos que ainda não estão na solução
  remaining = remainingElements(elements, instance, size)

  # Pega elementos mais proximos
  bestElements = generateBestElements(elements, remaining, instance)

  # Pegar um indice dos melhores
  rSize = len(bestElements) - 1
  index = random.randint(0, rSize)

  # Retorna indice do elemento aleatorio
  return bestElements[index]['index']

# Função para criar o caminho
def generatePath(instance):
  size = instance['size']

  # Gerar elemento inicial
  elements = generateInitialElement(size)

  # Constroe elementos com heuristica
  for index in range(size):
    elements.append(
      heuristicSearch(elements, instance, size)
    )

  return elements

# Função para avaliar caminho
def evaluatePath(path, instance):
  lIndex = path[-1]
  costs = []

  # Encontra custo de cada parte do caminho
  for index in path:
    costs.append(int(
      instance['matrix'][lIndex][index]
    ))

    lIndex = index

  return { 'path': path, 'cost': sum(costs) }

# Função para comparar caminhos por custo
def comparePaths(current, best):
  return current if current['cost'] <= best['cost'] else best

# Função de manipulação do algoritmo
def handleGreedySearch(instance):
  bestPath = { 'cost': sys.maxsize }
  sTime = time.time()

  while True:
    # Gerar caminho
    path = generatePath(instance)
    # Avaliar caminho
    evaluated = evaluatePath(path, instance)
    # Comparar caminhosbestPath
    bestPath = comparePaths(evaluated, bestPath)

    if (time.time() - sTime) >= instance['time']:
      break

  # Armazena tempo que levou para rodar algoritmo
  bestPath['time'] = time.time() - sTime

  return bestPath

# Função do algoritmo de busca local
def greedySearch(instance):
  solutions = []

  # Gerar tempos de execução
  instance['time'] = calculateTime(instance)

  # Faz as 10 buscas locais
  for index in range(10):
    solutions.append( handleGreedySearch(instance) )
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
    'BCGα',
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

# # ------ Programa ------
fileNames = ['Djibouti', 'Qatar', 'Uruguay', 'Western Sahara', 'Zimbabwe']
outputs = []

# Faz a leitura dos dados do arquivo
instaceList = readPreparedInstances(fileNames)

# Percorre cada instancia
for instance in instaceList:

  # Executa algoritmo de busca local
  instance['solutions'] = greedySearch(instance)

  # Monta saida
  instanceOutput = mountInstanceOutput(instance)

  # Adiciona saida da instancia as saidas
  outputs.append(instanceOutput)

# Escreve saidas no arquivo
writeOutput(outputs)
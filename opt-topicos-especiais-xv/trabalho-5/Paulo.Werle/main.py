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

# Função para calcular se o feromonio melhora ou piora
def calculatePheromoneCoefficient(current, best):
  return 1.2 if current['cost'] <= best['cost'] else 0.8

# Função para gerar array inicial
def generateInitialElement(size):
  return [random.randint(0, size)]

# Função para comparar caminhos por custo
def comparePaths(current, best):
  return current if current['cost'] <= best['cost'] else best

# Função para gerar matriz de feromonios
def generatePheromones(instance):
  # TODO - Acrescentado um para multiplicar numeros
  size = instance['size'] + 1
  return [[size for line in range(size)] for matrix in range(size)]

# Função para ver quais são os elementos restantes
def remainingElements(elements, instance, size):
  # TODO - Incluido um pq o range não pega o elemento max
  allElements = set(range(size + 1))
  current = set(elements)

  return list(allElements - current)

# Função para gerar os melhores elementos
def generateElements(elements, remaining, instance):
  lIndex = elements[-1]
  pheromoneByCosts = 0
  results = []

  # Percorre restantes para saber custo e feromonio existente
  for index in remaining:
    pheromone = int( instance['pheromones'][lIndex][index] )
    cost      = int( instance['matrix'][lIndex][index]     )

    results.append({ 'index': index, 'pheromoneByCost': (pheromone/cost) })
    pheromoneByCosts += pheromone/cost

  # Pega soma dos custos pelos feromonios em %
  for result in results:
    result['chance'] = math.ceil(
      (result['pheromoneByCost']/pheromoneByCosts) * 100
    )

  return results

# Função para pegar elemento de acordo com a sua chance
def getElementByPercentage(elements):
  array = []

  for element in elements:
    array = [*array, *([element['index']] * element['chance'])]

  # Pegar um indice dos melhores
  rSize = len(array) - 1
  index = random.randint(0, rSize)

  return array[index]

# Função para fazer a busca heuristica
def heuristicSearch(elements, instance, size):
  # Pega elementos que ainda não estão na solução
  remaining = remainingElements(elements, instance, size)

  # Pega elementos de acordo com a sua chance de ser o proximo
  bestElements = generateElements(elements, remaining, instance)

  # Pega elemento aleatoriamente pelo percentual
  element = getElementByPercentage(bestElements)

  return element

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

# Função para atualizar feromonios
def updatePheromones(evaluated, bestPath, instance):
  coefficient = calculatePheromoneCoefficient(evaluated, bestPath)
  lIndex = evaluated['path'][-1]

  # Atualiza feromonio de cada parte do caminho
  for index in evaluated['path']:
    value = (instance['pheromones'][lIndex][index] * coefficient)

    instance['pheromones'][lIndex][index] = round(value)
    instance['pheromones'][index][lIndex] = round(value)

    lIndex = index

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

# Função de manipulação do algoritmo
def handleSearchForAntColony(instance):
  bestPath = { 'cost': sys.maxsize }
  sTime = time.time()

  # Gerar matrix de feromonios
  instance['pheromones'] = generatePheromones(instance)

  while True:
    # Gerar caminho
    path = generatePath(instance)

    # Avaliar caminho
    evaluated = evaluatePath(path, instance)

    # Atualiza lista de feromonios
    updatePheromones(evaluated, bestPath, instance)

    # Comparar caminhos
    bestPath = comparePaths(evaluated, bestPath)

    if (time.time() - sTime) >= instance['time']:
      break

  # Armazena tempo que levou para rodar algoritmo
  bestPath['time'] = time.time() - sTime

  return bestPath

# Função do algoritmo de busca por colonia de formigas
def searchForAntColony(instance):
  solutions = []

  # Gerar tempos de execução
  instance['time'] = calculateTime(instance)

  # Faz as 10 buscas locais
  for index in range(10):
    solutions.append( handleSearchForAntColony(instance) )
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
    'BCCF',
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
  instance['solutions'] = searchForAntColony(instance)

  # Monta saida
  instanceOutput = mountInstanceOutput(instance)

  # Adiciona saida da instancia as saidas
  outputs.append(instanceOutput)

# Escreve saidas no arquivo
writeOutput(outputs)
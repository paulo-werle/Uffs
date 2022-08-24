import random
import math

# Função para calcular α
def calculateAlpha(orderedResults):
  return math.ceil(len(orderedResults) * 0.25)

# Função para gerar array inicial
def generateInitialElement(size):
  return [random.randint(0, size)]

# Função para ver quais são os elementos restantes
def remainingElements(elements, instance, size):

  # TODO: Incluido um pq o range não pega o elemento max
  allElements = set(range(size + 1))
  current = set(elements)

  return list(allElements - current)

# Função para gerar os melhores elementos
def generateBestElements(elements, remaining, instance):
  lIndex = elements[-1]
  results = []

  # Percorre restantes para saber custo
  for index in remaining:
    cost = int(instance['content'][lIndex][index])

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

# Função da busca construtiva
def constructiveSearch(instance):
  size = instance['size']

  # Gerar elemento inicial
  elements = generateInitialElement(size)

  # Constroe elementos com heuristica
  for _ in range(size):
    elements.append(
      heuristicSearch(elements, instance, size)
    )

  return elements
# ########## BIBLIOTECAS ##########
import math
import time
import random
import sys
import numpy as np

# ########## FUNÇÕES ##########
# - Função para avaliar soluações
def makespan(instance, solution):
  instanceSize = len(instance)
  time = [0] * instanceSize
  task = [0] * len(solution)

  for attempt in solution:
    if task[attempt - 1] == 1:
      return "SOLUÇÃO INVÁLIDA: task repetida!"
    else:
      task[attempt - 1] = 1

    for size in range(instanceSize):
      if time[size] < time[size - 1] and size != 0:
        time[size] = time[size - 1]

      time[size] += instance[size][attempt - 1]

  return time[instanceSize - 1]

# - Função para ler arquivos e retornar as instancias
def readInstances(fileList):
  instanceList = []

  # Percorre lista de arquivos
  for fileObject in fileList:

    # Monta começo e final da leitura
    readStart = 3
    readEnd = fileObject['machinesNumber'] + 3

    # Abre o arquivo e o percorre
    lines = []
    with open( f"Arquivos-Algoritmos-Genéticos/{fileObject['name']}", 'r' ) as file:
      for index, line in enumerate(file):
        if index in range(readStart, readEnd):
          lines.append( list(map(int, line.split() )) )

    # Coloca nome e linhas do arquivo na lista de instancias
    instanceList.append({
      'name':           fileObject['name'],
      'jobsNumber':     fileObject['jobsNumber'],
      'machinesNumber': fileObject['machinesNumber'],
      'lines':          lines
    })

  # Retorna a lista de instancias
  return instanceList

# - Função para criar a população inicial aleatoriamente
def createInitialPopulation(instance, size):
  population = [
    np.random.choice(instance['jobsNumber'], instance['jobsNumber'], replace=False)
    for i in range(size)
  ]

  return population

# - Função para avaliar a população
def evaluatePopulation(instance, population):
  evaluatedPopulation = []

  # Percorre população para testar soluções e guarda a população e o tempo
  for solution in population:
    evaluatedPopulation.append({
      'population': solution,
      'aptitude': makespan(instance['lines'], list(solution) )
    })

  # Ordena população de acordo com a avaliação
  sortedPopulation = sorted(evaluatedPopulation, key = lambda obj: obj['aptitude'])

  return sortedPopulation

# - Função para selecionar a população
def selectPopulation(evaluatedPopulation, populationSize):
  relationship = []
  half = round(populationSize / 2)

  for index in range(half):
    relationship.append([
      evaluatedPopulation[index],
      evaluatedPopulation[half - index]
    ])

  for index in range(half):
    relationship.append([
      evaluatedPopulation[random.randint(0, populationSize - 1)],
      evaluatedPopulation[random.randint(0, populationSize - 1)]
    ])

  return relationship

# - Função para calcula tamanho da população
def calcPopulationSize(instance):
  number = math.pow(
    instance['jobsNumber'], math.log10( instance['jobsNumber'] )
  )

  return math.ceil(number / 2.0) * 2

# - Função para fazer a recombinação e gerar soluções filhas
def recombination(selectedPopulation, instance):
  children = []
  defaultList = list(range(20))

  for parents in selectedPopulation:
    # Gera indice de corte
    randomHalf = random.randint(0, instance['jobsNumber'])

    # Cria filho apartir do corte dos pais
    child = np.array([
      *parents[0]['population'][:randomHalf],
      *parents[1]['population'][randomHalf:]
    ])

    # Pega elementos duplicados e os que não tem no filho
    duplicates = [index for index, val in enumerate(child) if val in child[:index]]
    missings = list( set(child).symmetric_difference(set(defaultList)) )

    # Substitui elementos duplicados pelos que não tem
    for index, duplicatesIndex in enumerate(duplicates):
      child[duplicatesIndex] = missings[index]

    children.append(child)

  return children

# - Função para realizar uma mutação na solução
def shift(newSolution, instance):

  for solution in newSolution:
    swapIndex = [
      random.randint(0, instance['jobsNumber'] - 1),
      random.randint(0, instance['jobsNumber'] - 1)
    ]

    tmp = solution[ swapIndex[0] ]
    solution[ swapIndex[0] ] = solution[ swapIndex[1] ]
    solution[ swapIndex[1] ] = tmp

  return newSolution

def updateBestSolution(evaluatedPopulation, bestSolution):
  # Pega primeira população, pois elas vão estar ordenadas pela aptidão
  currentBestSolution = evaluatedPopulation[0]

  if bestSolution['aptitude'] > currentBestSolution['aptitude']:
    bestSolution = currentBestSolution

  return bestSolution

########## PROGRAMA PRINCIPAL ##########

fileList = [
  { 'name': 'tai20_5.txt',   'jobsNumber': 20,  'machinesNumber': 5  },
  # { 'name': 'tai20_10.txt',  'jobsNumber': 20,  'machinesNumber': 10 },
  # { 'name': 'tai20_20.txt',  'jobsNumber': 20,  'machinesNumber': 20 },
  # { 'name': 'tai50_5.txt',   'jobsNumber': 50,  'machinesNumber': 5  },
  # { 'name': 'tai50_10.txt',  'jobsNumber': 50,  'machinesNumber': 10 },
  # { 'name': 'tai50_20.txt',  'jobsNumber': 50,  'machinesNumber': 20 },
  # { 'name': 'tai100_5.txt',  'jobsNumber': 100, 'machinesNumber': 5  },
  # { 'name': 'tai100_10.txt', 'jobsNumber': 100, 'machinesNumber': 10 },
  # { 'name': 'tai100_20.txt', 'jobsNumber': 100, 'machinesNumber': 20 },
  # { 'name': 'tai200_10.txt', 'jobsNumber': 200, 'machinesNumber': 10 },
]

# Le instancias
instanceList = readInstances(fileList)
# Percorre instancias
for instance in instanceList:
  # Calcula tamanho da população
  populationSize = calcPopulationSize(instance)
  # Executa 10 vezes cada instancia
  for instanceAttempt in range(10):
    # Monta melhor solução para execução
    bestSolution = { 'population': [], 'aptitude': sys.maxsize, 'endTime': 0 }
    # Começa a marcar o tempo
    startTime = time.time()
    # Cria população inicial
    population = createInitialPopulation(instance, populationSize)
    # Percorre até chegar em uma condição de break
    while True:
      if 1 <= time.time() - startTime:
        break
      if False:
        break
      # Avalia a população
      evaluatedPopulation = evaluatePopulation(instance, population)
      # Atualiza a melhor solução
      bestSolution = updateBestSolution(evaluatedPopulation, bestSolution)
      # Seleciona as populações
      selectedPopulation = selectPopulation(evaluatedPopulation, populationSize)
      # Recombinar amostras
      newSolution = recombination(selectedPopulation, instance)
      # Faz uma mutação nas amostras
      newSolution = shift(newSolution, instance)
      # Seleciona a nova nova geração para ser a população
      population = newSolution
    # Grava tempo final
    bestSolution['endTime'] = time.time() - startTime

    print(bestSolution)


########## Anotações ##########
# Ler arquivos com instancias
#   - Deve se ler apenas a primeira instancia de cada arquivo
#   - Ver qual dados vamos usar para poder montar na instancia
#   -> lerInstancias(lista de arquivos)

# Marcar tempo inicial de execução
#   - Utilizar time para marcar tempo inicial
#   -> tempoInicial = time.time()

# Gerar sequencia de tarefas aleatorias
#   - As sequencias de tarefas, devem conter o numero de tarefas
#   - Ver quantos dados vamos gerar
#     - math.round(
#       math.pow (
#         math.log( math.factorial(NUMERO_DE_TAREFAS) ),
#         math.log( math.factorial(NUMERO_DE_MAQUINAS) )
#       )
#     )

# Pegar sequencia de tarefas e avaliar
#   - Avaliar sequencia de tarefas usando o codigo do professor
#   -> makespan(instancia, solução)

# Observar se os criterios de paradas foram atendidos
#   - Criterio de tempo maximo
#   - Criterio que se o programa não apresentar um tempo melhor nas 10 proximas gerações para

# Recombinar sequencia de tarefas
#   - Gerar sequencia de soluções filhas
#   - Ver qual tipo de dencedencia vamos usar
#   - Vamos ver ainda

# Fazer a mutação das sequencias de tarefas
#   - Fazer uma pequena alteração nos dados
#   -> Sortear numero de elementos baseado no NUMERO_DE_TAREFAS para trocar de posição

# Marcar tempo total final
#   -> time.time() - tempoInicial

# Deve se executar tudo 10 vezes para cada instancia

# Fazer calculos necessarios

# Pegar dados para montar relatorio
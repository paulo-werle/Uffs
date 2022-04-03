# Importando bibliotecas
import math
import time
import random
import numpy as np

# Definindo funções
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

def createInitialPopulation(instance, size):
  population = [
    np.random.choice(instance['jobsNumber'], instance['jobsNumber'], replace=False)
    for i in range(size)
  ]

  return population

def evaluatePopulation(instance, population):
  evaluatedPopulation = []

  # Percorre população para testar soluções e guarda a população e o tempo
  for solution in population:
    evaluatedPopulation.append({
      'population': solution,
      'time': makespan(instance['lines'], list(solution) )
    })

  # Ordena população de acordo com a avaliação
  sortedPopulation = sorted(evaluatedPopulation, key = lambda obj: obj['time'])

  return sortedPopulation

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

  print(len(relationship))

def calcPopulationSize(instance):
  number = math.pow(
    instance['jobsNumber'], math.log10( instance['jobsNumber'] )
  )

  return math.ceil(number / 2.0) * 2

# Iniciando Programa

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

  # Define a propria estancia como a melhor
  # bestSolutions = instance

  # Calcula tamanho da população
  populationSize = calcPopulationSize(instance)

  # for instanceAttempt in range(10):
    # bestSolution = {'solution': [],'aptitude': sys.maxint,'finalTime': 0}

  # Inicia tempo
  # startTime = time.time()

  # Cria população inicial
  population = createInitialPopulation(instance, populationSize)

  # while true:
  #   if 180 <= time.time() - tempoInicial:
  #     break
  #   if criterioParada2 == true:
  #     break

  # Avalia a população
  evaluatedPopulation = evaluatePopulation(instance, population)

  # Define a melhor solução atual
  bestCurrentSolution = evaluatedPopulation[0]

  # Seleciona as populações
  selectedPopulation = selectPopulation(evaluatedPopulation, populationSize)

  # Recombinar amostras
  # recombination(selectedPopulation)


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
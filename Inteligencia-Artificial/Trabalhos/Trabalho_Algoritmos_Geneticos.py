# ########## BIBLIOTECAS ##########
import math
import time
import random
import sys
import csv
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
    list( map(
      lambda number: int(number + 1),
      np.random.choice(instance['jobsNumber'], instance['jobsNumber'], replace=False)
    )) for i in range(size)
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
  defaultList = list(range(1, instance['jobsNumber'] + 1))

  for parents in selectedPopulation:
    # Gera indice de corte
    randomHalf = random.randint(0, instance['jobsNumber'] - 1)

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

# - Função para atualizar a melhor solução
def updateBestSolution(evaluatedPopulation, bestSolution):
  # Pega primeira população, pois elas vão estar ordenadas pela aptidão
  currentBestSolution = evaluatedPopulation[0]

  if bestSolution['aptitude'] > currentBestSolution['aptitude']:
    bestSolution = currentBestSolution

  return bestSolution

# - Função para gerar relatorio
def saveReport(report):
  # Abre o arquivo no modo escrita
  with open( "report.csv", 'w' ) as file:

    # Cria writer e escreve header
    writer = csv.writer(file)
    writer.writerow([
      'Instancia',       'Lower bound',             'Upper bound',
      'Média (Aptidão)', 'Desvio padrão (Aptidão)', 'Variancia (Aptidão)', 'Mediana (Aptidão)',
      'Média (Tempo)',   'Desvio padrão (Tempo)',   'Variancia (Tempo)',   'Mediana (Tempo)'
    ])

    # Pega dados da instancia e escreve body
    for instance in report:
      aptitudes = [item['aptitude'] for item in instance['solutions']]
      times = [item['endTime'] for item in instance['solutions']]

      print(instance['name'], aptitudes, times)
      writer.writerow([
        instance['name'],   min(aptitudes),    max(aptitudes),
        np.mean(aptitudes), np.std(aptitudes), np.var(aptitudes), np.median(aptitudes),
        np.mean(times),     np.std(times),     np.var(times),     np.median(times)
      ])

    # Fecha arquivo
    file.close()

########## PROGRAMA PRINCIPAL ##########
fileList = [
  { 'name': 'tai20_5.txt',   'jobsNumber': 20,  'machinesNumber': 5  },
  { 'name': 'tai20_10.txt',  'jobsNumber': 20,  'machinesNumber': 10 },
  { 'name': 'tai20_20.txt',  'jobsNumber': 20,  'machinesNumber': 20 },
  { 'name': 'tai50_5.txt',   'jobsNumber': 50,  'machinesNumber': 5  },
  { 'name': 'tai50_10.txt',  'jobsNumber': 50,  'machinesNumber': 10 },
  { 'name': 'tai50_20.txt',  'jobsNumber': 50,  'machinesNumber': 20 },
  { 'name': 'tai100_5.txt',  'jobsNumber': 100, 'machinesNumber': 5  },
  { 'name': 'tai100_10.txt', 'jobsNumber': 100, 'machinesNumber': 10 },
  { 'name': 'tai100_20.txt', 'jobsNumber': 100, 'machinesNumber': 20 },
  { 'name': 'tai200_10.txt', 'jobsNumber': 200, 'machinesNumber': 10 },
]

# Le instancias
instanceList = readInstances(fileList)
# Monta relatorio inicial
report = [ dict({ 'name': instance['name'], 'solutions': [] }) for instance in instanceList ]
# Percorre instancias
for index, instance in enumerate(instanceList):
  # Calcula tamanho da população
  populationSize = calcPopulationSize(instance)
  # Inicia melhores soluções de acordo com relatorio
  bestSolutions = report[index]['solutions']
  # Executa 10 vezes cada instancia
  for instanceAttempt in range(10):
    # Monta melhor solução para execução
    bestSolution = { 'population': [], 'aptitude': sys.maxsize, 'endTime': 0 }
    # Começa a geração
    generationNumber = 0
    # Começa a marcar o tempo
    startTime = time.time()
    # Cria população inicial
    population = createInitialPopulation(instance, populationSize)
    # Percorre até chegar em uma condição de break
    while True:
      if 30 <= time.time() - startTime:
        print(f"Finalizado {instanceAttempt} - {instance['name']}")
        break
      if generationNumber >= 500:
        print(f"Finalizado {instanceAttempt} - {instance['name']}")
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
      # Atualiza numero da geração
      generationNumber += 1
    # Grava tempo final
    bestSolution['endTime'] = time.time() - startTime
    # Junta solução com outras
    bestSolutions.append(bestSolution)
  # Ajusta relatorio com soluções
  report[index]['solutions'] = bestSolutions
# Gera relatorio dos resultados
saveReport(report)
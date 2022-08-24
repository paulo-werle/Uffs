# # ------ Bibliotecas ------
from sys       import maxsize
from threading import Semaphore
from threading import Thread
from time      import sleep
from time      import time

# # ------ Arquivos ------
from includes.files              import readFiles
from includes.files              import writeFile
from includes.helpers            import calculateTime
from includes.helpers            import mountInstanceOutput
from includes.searchConstructive import constructiveSearch
from includes.searchLocal        import localSearch

# ------ Variables ------
executionSemaphore    = Semaphore()
constructiveSemaphore = Semaphore()
localSemaphore        = Semaphore()

constructiveSolution = []
localSolution        = []
executionSolution    = []

# ------ Funções ------

def executionFn(instance, sTime):
  constructiveSemaphore.acquire()
  localSemaphore.acquire()

  # solution = { 'cost': maxsize }


  while True:
    executionSemaphore.acquire()
    print("executionFn", time())

    # currentSolution = localSearch(
    #   constructiveSearch(instance), instance
    # )
    # if currentSolution['cost'] < solution['cost']:
    #   solution = currentSolution

    constructiveSemaphore.release()

    if (time() - sTime) >= instance['time']:
      break

def constructiveFn(instance, sTime):
  sTime = time()

  while True:
    constructiveSemaphore.acquire()
    print("constructiveFn", time())

    # constructiveSolution = constructiveSearch(instance)
    localSemaphore.release()

    if (time() - sTime) >= instance['time']:
      break


def localFn(instance, sTime):
  sTime = time()

  while True:
    localSemaphore.acquire()
    print("localFn", time())

    # localSolution = localSearch(instance)
    executionSemaphore.release()

    if (time() - sTime) >= instance['time']:
      break

def controlThreadsExecutions(instance):
  sTime = time()

  executionThread    = Thread(target = executionFn,    args = (instance, sTime))
  constructiveThread = Thread(target = constructiveFn, args = (instance, sTime))
  localThread        = Thread(target = localFn,        args = (instance, sTime))

  executionThread.start()
  constructiveThread.start()
  localThread.start()

  executionThread.join()
  constructiveThread.join()
  localThread.join()


  # solution = { 'cost': maxsize }
  # sTime = time()

  # while (time() - sTime) <= instance['time']:
    # currentSolution = localSearch(
    #   constructiveSearch(instance), instance
    # )

    # if currentSolution['cost'] < solution['cost']:
    #   solution = currentSolution

  # solution['time'] = time() - sTime
  # return solution

def controlExecutions(instance):
  solution = { 'cost': maxsize }
  sTime = time()

  while (time() - sTime) <= instance['time']:
    currentSolution = localSearch(
      constructiveSearch(instance), instance
    )

    if currentSolution['cost'] < solution['cost']:
      solution = currentSolution

  solution['time'] = time() - sTime
  return solution

def handleSearches(instance):
  instance['time'] = calculateTime(instance)
  tSolutions = []
  solutions = []

  # for index in range(10):
  #   solutions.append( controlExecutions(instance) )
  #   print(index, instance['name'], '- encerrou execução')
  # print(solutions)

  for index in range(10):
    tSolutions.append( controlThreadsExecutions(instance) )
    print(index, instance['name'], '- encerrou execução')
  print(tSolutions)

  # return solutions

# ------ Programa ------
fileNames = ['Uruguay']
outputs = []

# Faz a leitura dos dados do arquivo
instaceList = readFiles(fileNames)

# Percorre cada instancia
for instance in instaceList:

  instance['solutions'] = handleSearches(instance)

  # outputs.append( mountInstanceOutput(instance) )

# writeFile(outputs)


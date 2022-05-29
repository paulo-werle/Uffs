import math
import csv

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


# ------ Programa ------
fileNames = ['Western-Sahara']

instaceList = readInstances(fileNames)

for instance in instaceList:
  instance['adjacencyMatrix'] = createAdjacencyMatrix(instance)

writeInstances(instaceList)
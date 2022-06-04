import math
import csv

# ------ Funções ------
# Função para ler instancias
def readInstances(fileNames):
  # Inicia lista de instancias
  instanceList = []

  # Percorre cada arquivo
  for fileName in fileNames:
    with open( f"../instances/{fileName}.tsp", 'r' ) as file:
      instance = []
      lines = file.read().splitlines()

      # Define conteudo
      content = lines[(lines.index('NODE_COORD_SECTION') + 1):lines.index('EOF')]

      # Percorre cada linha do conteudo
      for line in content:
        values = line.split(' ')

        # Adiciona o conteudo na instancia
        instance.append({
          'index': int(values[0]),
          'xCoordinate': float(values[1]),
          'yCoordinate': float(values[2])
        })

    # Adiciona instancia na lista
    instanceList.append({
      'name': fileName,
      'content': instance
    })

  return instanceList

# Função para escrever instancias
def writeInstances(instaceList):

  # Percorre instancias
  for instace in instaceList:
    with open( f"../prepared-instances/{instace['name']}.csv", 'w' ) as file:

      # Percorre linhas da matrix de adjacencia
      for line in instace['adjacencyMatrix']:

        # Escreve cada linha em um csv
        writer = csv.writer(file)
        writer.writerow(line)

# Função para calcular a Distância euclidiana
def calculateEuclideanDistance(point1, point2):
  # Executa a seguinte operação: SQRT((x1-x2)^2+(y1-y2)^2)
  xValue = (point1['xCoordinate'] - point2['xCoordinate']) ** 2
  yValue = (point1['yCoordinate'] - point2['yCoordinate']) ** 2

  value = math.sqrt(xValue + yValue)

  return round(value)

# Função para criar matrix de adjacência
def createAdjacencyMatrix(instance):
  matrix = []

  # Percorre linhas do conteudo
  for xLine in instance['content']:
    array = []

    # Percorre linhas do conteudo
    for yLine in instance['content']:

      # Calcula a distancia de cada linhaX para cada linhaY
      array.append(
        calculateEuclideanDistance(xLine, yLine)
      )

    matrix.append(array)

  return matrix

# ------ Programa ------
# Define arquivos a serem usados
fileNames = ['Djibouti', 'Qatar', 'Uruguay', 'Western Sahara', 'Zimbabwe']

# Faz a leitura dos dados do arquivo
instaceList = readInstances(fileNames)

# Percorre cada instancia
for instance in instaceList:

  # Cria a matrix de adjacencia (Distancia das cidades)
  instance['adjacencyMatrix'] = createAdjacencyMatrix(instance)

# Escreve instancias em arquivos
writeInstances(instaceList)
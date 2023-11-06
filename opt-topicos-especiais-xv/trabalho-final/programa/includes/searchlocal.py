# Gera caminho de acordo com indices - 2OPT
def generatePath(solution, xId, yId):
  minId = min(xId, yId)
  maxId = max(xId, yId)

  return [
    *solution[:minId], *reversed(solution[minId:maxId]), *solution[maxId:]
  ]

# Função para analisar o caminho
def analyzePath(solution, instance):
  content = instance['content']
  lIndex = solution[-1]
  result = []

  # Percorre cada parte do caminho para encontrar custo
  for cIndex in solution:
    result.append(int( content[lIndex][cIndex] ))
    lIndex = cIndex

  return { 'path': solution, 'cost': sum(result) }

# Função para fazer a busca heuristica
def heuristicSearch(solution, instance):
  size = instance['size']

  # Percorre dados para fazer o 2opt
  for xId in range(size):
    for yId in range(size):
      if xId != yId:

        # Gera caminho com 2OPT
        localSolution = analyzePath(
          generatePath(solution['path'], xId, yId),
          instance
        )

        # Caso achar a Primeira melhor, retorna
        if localSolution['cost'] < solution['cost']:
          return localSolution

# Função de busca local
def localSearch(solution, instance):
  localSolution = heuristicSearch(
    analyzePath(solution, instance),
    instance
  )

  return localSolution


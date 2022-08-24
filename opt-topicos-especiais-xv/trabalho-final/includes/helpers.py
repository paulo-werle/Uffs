import statistics

# Função para calcular tempos
def calculateTime(instance):
  return (instance['size'] * 60) / 1000

# Função para montar a saida da instancia
def mountInstanceOutput(instance):
  costValues = []
  timeValues = []

  # Percorre calculando soluções
  for solution in instance['solutions']:
    costValues.append(solution['cost'])
    timeValues.append(solution['time'])

  return [
    instance['name'],
    'Paulo.Werle',
    'BCGα.BLPM2opt',
    round(statistics.mean(costValues)),
    round(statistics.stdev(costValues), 2),
    round(statistics.mean(timeValues))
  ]
# Metodo de lagrange
def lagrange(x, y, xPoint):
  yPoint = 0
  length = len(x)

  for i in range(length):
    p = 1

    for j in range(length):
        if i != j:
            p = p * (xPoint - x[j])/(x[i] - x[j])

    yPoint = yPoint + p * y[i]

  print('Lagrange: (%.6f, %.6f)' % (xPoint, yPoint))

# Entradas
x = [0.00, 1.00, 2.00]
y = [1.31, 3.51, 3.78]
xp = 3.63

# Execução
lagrange(x, y, xp)
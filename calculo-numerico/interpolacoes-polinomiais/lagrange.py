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
x = [1.00, 2.00, 3.00]
y = [6.00, 3.00, 2.00]
xp = 2.2

# Execução
lagrange(x, y, xp)
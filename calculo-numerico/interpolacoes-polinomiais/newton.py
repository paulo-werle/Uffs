def newton(x, y, xPoint):
  table = [y]
  length = len(x)
  step = 1

  for n in range(length - 1):
    order = []

    for m in range(len(table[n]) - 1):
      order.append(
        (table[n][m+1] - table[n][m]) / (x[m + step] - x[m])
      )
    table.append(order)
    step +=1

  # for k in range(len(table)):
  #   print("Ordem %d:" %k, table[k])

  yPoint = 0
  grade = 0

  for i in range(len(table)):
    factor = table[i][0]

    for j in range(grade):
      factor *=(xPoint - x[j])

    grade += 1
    yPoint += factor

  print('Newton: (%.6f, %.6f)' % (xPoint, yPoint))

# Entradas
x = [0.00, 1.00, 2.00]
y = [1.31, 3.51, 3.78]
xp = 3.63

newton(x, y, xp)
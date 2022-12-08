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
x = [1.00, 2.00, 3.00]
y = [6.00, 3.00, 2.00]
xp = 2.2

newton(x, y, xp)
from numpy import zeros

def gaussSeidel(a, b, N = 25, x = None):
  # Cria chute inicial
  if x is None:
    x = zeros(len(a[0]))

  for i in range(N):

    # Pega a quantidade de equações
    length = len(a)

    # Calcula os x para a quantidade de equações presentes
    for eql in range(0, length):
      # Define valor da solução da equação b
      eqlResult = b[eql]

      # Calcula respectivamente cada x
      for index in range(0, length):
        if (eql != index):
          eqlResult -= a[eql][index] * x[index]

      # Atualiza o valor da sua solução
      x[eql] = eqlResult / a[eql][eql]

    print(i, x)

  # Retorna a solução atualizada
  return x

# Entradas
a = [
  [ 4.0,  2.0,  2.0, -1.0, 1.0],
  [-1.0,  5.0,  0.0, -1.0, 1.0],
  [ 1.0, -1.0,  4.0, -1.0, 1.0],
  [ 1.0, -2.0,  1.0, -6.0, 1.0],
  [ 1.0, -1.0,  1.0, -1.0, 7.0],
]

b = [5.0, 2.0, 2.0, 1.0, 3.0]

# Saida
print("Solução:", gaussSeidel(a, b))
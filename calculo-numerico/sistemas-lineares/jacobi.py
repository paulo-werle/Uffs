# from pprint import pprint
from numpy import array, zeros, diag, diagflat, dot

# Resolvendo equação atravez do metodo interativo de jacobi
def jacobi(A, b, N = 25, x = None):
  # Cria chute inicial
  if x is None:
    x = zeros(len(A[0]))

  # Cria o vetor com os elementos da diagonal de A e subtrai de A
  D = diag(A)
  R = A - diagflat(D)

  # Interage por N vezes calculando
  for i in range(N):
    x = (b - dot(R,x)) / D
    print(i, x)

  return x

# Entradas
A = array([
  [2.0, 1.0],
  [1.0, 5.0]
])

b = array(
  [1.0, 3.0]
)

guess = array(
  [1.0, 2.0]
)

# Saida
print("Solução:", jacobi(A, b))

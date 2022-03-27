# Importando a biblioteca
import numpy as np

# Função do cáculo da sigmóide
def sigmoid(x):
  return 1/(1+np.exp(-x))

# Derivada da função sigmóide
def sigmoid_prime(x):
  return sigmoid(x) * (1 - sigmoid(x))

# Vetor dos valores de entrada e saídas
x = np.array([1, 2, 3, 4])
y = np.array(0.5)
b= 0.5

# Pesos iniciais das ligações sinápticas
w = np.random.randn(4)/10

# Taxa de Aprendizagem
learnrate = 0.5

# Calcule um degrau de descida gradiente para cada peso
# Critério de parada
#   Epochs: Número de Épocas
#   MinError: Erro mínimo estipulado

#Número de Épocas
epochs=10

#Inicilizando del_w
del_w=0

for e in range(epochs):
  h = np.dot(x, w)                      # TODO: Calcule a combinação linear de entradas e pesos sinápticos
  output = sigmoid(h)                   # TODO: Calcule a saída da Rede Neural
  error = y - output                    # TODO: Calcule o erro da Rede Neural
  error_term = error * sigmoid_prime(h) # TODO: Calcule o termo de erro
  del_w = learnrate * error_term * x    # TODO: Calcule a variação do peso
  w = w + del_w                         # TODO: Atualização do Peso
  
print('Saída da Rede Neural:')
print(output)
print('Erro:')
print(error)
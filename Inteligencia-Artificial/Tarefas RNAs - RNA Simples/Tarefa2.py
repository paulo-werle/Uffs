# Importando a biblioteca
import numpy as np

# Função do cáculo da sigmóide
def sigmoid(h):
  return 1 / (1 + np.exp(-h))

# Derivada da sigmóide
def sigmoid_prime(x):
  return sigmoid(x) * (1 - sigmoid(x))

# Vetor dos valores de entrada
x = np.array([1, 2, 3, 4])
y = np.array(0.5)
b = 0.5

# Pesos das ligações sinápticas
w = np.array([0.5, -0.5, 0.3, 0.1])

# Taxa de aprendizagem
learnrate = 0.5

# Calculo de um degrau de decida gradiente para cada peso
h = np.dot(x, w) + b                  # TODO: Calcule a combinação linear de entradas e pesos sinápticos
nn_output = sigmoid(h)                # TODO: Calcule a saida da Rede Neural
error = y - nn_output                 # TODO: Calcule o erro da Rede Neural
error_term = error * sigmoid_prime(h) # TODO: Calcule o termo de erro 
# Lembre-se, isso requer o gradiente de saída, para o qual não  adicionamos especificamente uma variável. 
del_w = learnrate * error_term * x    # TODO: Calcule a mudança nos pesos

print(nn_output)
print(error)
print(del_w)
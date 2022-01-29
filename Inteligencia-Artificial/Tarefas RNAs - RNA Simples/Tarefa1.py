# Importando a biblioteca
import numpy as np

# Função do cáculo da sigmóide
def sigmoid(h):
  return 1/(1+np.exp(-h))

# Vetor dos valores de entrada
x = np.array([0.8,-0.3])
b = 0.1

# Pesos das ligações sinápticas
w = np.array([0.2,-0.1])

# Calcule a combinação linear de entradas e pesos sinápticos
h = np.dot(x,w)+b

# Aplicado a função de ativação do neurônio
y = sigmoid(h)
print('A saída da rede é',y)
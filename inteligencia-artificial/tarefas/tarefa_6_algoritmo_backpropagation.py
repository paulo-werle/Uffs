import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
%matplotlib inline
from sklearn.model_selection import train_test_split

# Função do cáculo da sigmóide
def sigmoid(x):
  return 1/(1+np.exp(-x))

# Carregando os dados
DataSet = pd.read_csv('Data.csv')

X_train, X_test, y_train, y_test = train_test_split(
  DataSet.drop(['Output1', 'Output2'], axis=1),
  DataSet[['Output1', 'Output2']], test_size=0.30, random_state=101
)

# Tamanho do DataSet de Treinamento
n_records, n_features = X_train.shape

# Arquitetura da MPL
N_input = 3
N_hidden = 8
N_output = 2
learnrate = 0.5

# Tamanho do DataSet de Treinamento
n_records, n_features = X_train.shape

# Arquitetura da MPL
N_input = 3
N_hidden = 8
N_output = 2
learnrate = 0.5

# Pesos da Camada Oculta (Inicialização Aleatória)
weights_input_hidden = np.random.normal(0, scale=0.1, size=(N_input, N_hidden))
print('Pesos da Camada Oculta:')
print(weights_input_hidden)

# Pesos da Camada de Saída (Inicialização Aleatória)
weights_hidden_output = np.random.normal(0, scale=0.1, size=(N_hidden, N_output))
print('Pesos da Camada de Saída:')
print(weights_hidden_output)

# Algoritmo Backpropagation
epochs = 5000
last_loss=None
EvolucaoError=[]
IndiceError=[]

for e in range(epochs):
  delta_w_i_h = np.zeros(weights_input_hidden.shape)
  delta_w_h_o = np.zeros(weights_hidden_output.shape)

  for xi, yi in zip(X_train.values, y_train.values):

    # --- Forward Pass ---
    # Camada oculta
    hidden_layer_input = np.dot(xi, weights_input_hidden) # Calcule a combinação linear de entradas e pesos sinápticos
    hidden_layer_output = sigmoid(hidden_layer_input)     # Aplicado a função de ativação

    # Camada de Saída
    output_layer_in = np.dot(hidden_layer_output, weights_hidden_output) # Calcule a combinação linear de entradas e pesos sinápticos

    # Aplicado a função de ativação
    output = sigmoid(output_layer_in)

    # --- Backward Pass ---
    error = yi - output                                                                # TODO: Cálculo do Erro
    output_error_term = error * output * (1 - output)                                  # TODO: Calcule o termo de erro de saída (Gradiente da Camada de Saída)
    hidden_error = np.dot(weights_hidden_output,output_error_term)                     # TODO: Calcule a contribuição da camada oculta para o erro
    hidden_error_term = hidden_error * hidden_layer_output * (1 - hidden_layer_output) # TODO: Calcule o termo de erro da camada oculta (Gradiente da Camada Oculta)
    delta_w_h_o += output_error_term*hidden_layer_output[:, None]                      # TODO: Calcule a variação do peso da camada de saída
    delta_w_i_h += hidden_error_term * xi[:, None]                                     # TODO: Calcule a variação do peso da camada oculta

  # Atualização dos pesos na época em questão
  weights_input_hidden += learnrate * delta_w_i_h / n_records
  weights_hidden_output += learnrate * delta_w_h_o / n_records

  # Imprimir o erro quadrático médio no conjunto de treinamento
  if (e % (epochs / 20) == 0):
    hidden_output = sigmoid(np.dot(xi, weights_input_hidden))
    out = sigmoid(np.dot(hidden_output, weights_hidden_output))
    loss = np.mean((out - yi) ** 2)/2

    if (last_loss and last_loss < loss):
      print("Erro quadrático no treinamento: ", loss, " Atenção: O erro está aumentando")
    else:
      print("Erro quadrático no treinamento: ", loss)

    last_loss = loss
    EvolucaoError.append(loss)
    IndiceError.append(e)

# Gráfico da Evolução do Erro
plt.plot(IndiceError, EvolucaoError, 'r') # 'r' = red
plt.xlabel('')
plt.ylabel('Erro Quadrático')
plt.title('Evolução do Erro no treinamento da MPL')
plt.show()

# Validação do modelo
# Calcule a precisão dos dados de teste
n_records, n_features = X_test.shape
MSE_Output1=0
MSE_Output2=0

for xi, yi in zip(X_test.values, y_test.values):

  # --- Forward Pass ---
  # Camada oculta
  hidden_layer_input = np.dot(xi, weights_input_hidden) # Calcule a combinação linear de entradas e pesos sinápticos
  hidden_layer_output = sigmoid(hidden_layer_input)     # Aplicado a função de ativação

  # Camada de Saída
  output_layer_in = np.dot(hidden_layer_output, weights_hidden_output) # Calcule a combinação linear de entradas e pesos sinápticos

  # Aplicado a função de ativação
  output = sigmoid(output_layer_in)

  # Cálculo do Erro
  error = yi - output
  MSE_Output1 += (yi[0] - output[0])**2
  MSE_Output2 += (yi[1] - output[1])**2

# Erro Quadrático Médio
MSE_Output1/=n_records
MSE_Output2/=n_records

print('Erro Quadrático Médio da Saída Output1 é: ',MSE_Output1)
print('Erro Quadrático Médio da Saída Output2 é: ',MSE_Output2)
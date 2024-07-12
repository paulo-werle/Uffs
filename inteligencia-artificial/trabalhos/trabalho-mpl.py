# Modelo para o Sensor CEI
# Este dataset "arruela_.csv" possui informações dispostas em colunas sobre as características dos objetos que passam pelo sensor:

# Tamanho: Segue a classificação do Dataset
# Referencia: Referência dinâmica do *Threshold.
# NumAmostra: Número de amostras adquiridas.
# Area: Somatório das Amplitudes das amostras.
# Delta: Máxima Amplitude da amostra.
# Output1: Peça tipo 1.
# Output2: Peça tipo 2.

# Bibliotecas
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
%matplotlib inline

# Função do cáculo da sigmóide
def sigmoid(x):
  return 1/(1+np.exp(-x))

# Carregando os dados
## Vamos começar lendo o arquivo DataCEI.csv em um dataframe do pandas.
DataSet=pd.read_csv('arruela_.csv')

## Desconsiderando alguns dados
DataSet.drop(['Hora','Tamanho'],axis=1,inplace=True)

## Váriaveis do Dataset
# DataSet.columns
# DataSet.head()

# Relação entre as variáveis preditoras
## Mapa de Calor
sns.heatmap(DataSet.corr())
plt.title('Mapa de Calor')
plt.show()
print("\n")

# Normalização dos Dados
scaler=StandardScaler()
DataScaled=scaler.fit_transform(DataSet)
DataSetScaled=pd.DataFrame(np.array(DataScaled),columns = ['Referencia', 'NumAmostra', 'Area', 'Delta', 'Output1','Output2'])

# Conjunto de dados para o treinamento
X = DataSetScaled.drop(['Output1', 'Output2'],axis=1)
y = DataSet[['Output1','Output2']]

# Separando os dados de treinamento e de validação
## Iremos separar de forma randômica 33% dos dados para validação
## Estes dados não serão utilizados para determinação dos coeficientes preditores do modelo
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.30, random_state=101)
# print(y_test)
# print(X_test)

# Criando o Modelo de MPL
## Tamanho do DataSet de Treinamento
n_records, n_features = X_train.shape

# Arquitetura da MPL
N_input = 4
N_hidden = 8
N_output = 2
learnrate = 0.4

# Inicialização dos pesos da MPL (Aleatório)
weights_input_hidden = np.random.normal(0, scale=0.1, size=(N_input, N_hidden))   # Pesos da Camada Oculta (Inicialização Aleatória)
weights_hidden_output = np.random.normal(0, scale=0.1, size=(N_hidden, N_output)) # Pesos da Camada de Saída (Inicialização Aleatória)
# print('Pesos da Camada Oculta:', weights_input_hidden)
# print('Pesos da Camada de Saída:', weights_hidden_output)

# Algoritmo Backpropagation
epochs = 20000
last_loss=None
EvolucaoError=[]
IndiceError=[]

for e in range(epochs):
  delta_w_i_h = np.zeros(weights_input_hidden.shape)
  delta_w_h_o = np.zeros(weights_hidden_output.shape)
  for xi, yi in zip(X_train.values, y_train.values):
        
    # ------ Forward Pass ------
    ## Camada oculta
    hidden_layer_input = np.dot(xi, weights_input_hidden) # Calcule a combinação linear de entradas e pesos sinápticos
    hidden_layer_output = sigmoid(hidden_layer_input)     # Aplicado a função de ativação

    ## Camada de Saída
    output_layer_in = np.dot(hidden_layer_output, weights_hidden_output) # Calcule a combinação linear de entradas e pesos sinápticos

    ## Aplicado a função de ativação 
    output = sigmoid(output_layer_in)
    
    # ------ Backward Pass ------
    error = yi - output                                                                # TODO: Cálculo do Erro
    output_error_term = error * output * (1 - output)                                  # TODO: Calcule o termo de erro de saída (Gradiente da Camada de Saída)
    hidden_error = np.dot(weights_hidden_output,output_error_term)                     # TODO: Calcule a contribuição da camada oculta para o erro
    hidden_error_term = hidden_error * hidden_layer_output * (1 - hidden_layer_output) # TODO: Calcule o termo de erro da camada oculta (Gradiente da Camada Oculta)
    delta_w_h_o += output_error_term*hidden_layer_output[:, None]                      # TODO: Calcule a variação do peso da camada de saída
    delta_w_i_h += hidden_error_term * xi[:, None]                                     # TODO: Calcule a variação do peso da camada oculta
        
  #Atualização dos pesos na época em questão
  weights_input_hidden += learnrate * delta_w_i_h / n_records
  weights_hidden_output += learnrate * delta_w_h_o / n_records
    
  # Imprimir o erro quadrático médio no conjunto de treinamento
  if  e % (epochs / 20) == 0:
    hidden_output = sigmoid(np.dot(xi, weights_input_hidden))
    out = sigmoid(np.dot(hidden_output, weights_hidden_output))
    loss = np.mean((out - yi) ** 2)

    if last_loss and last_loss < loss:
      print("Treinamento - erro quadrático: ", loss, " OBS: O erro está aumentando!")
    else:
      print("Treinamento - erro quadrático: ", loss)
    last_loss = loss
      
    EvolucaoError.append(loss)
    IndiceError.append(e)

# Gráfico da Evolução do Erro
print("\n")
plt.plot(IndiceError, EvolucaoError, 'r')
plt.title('Treinamento - Evlolução do erro da MPL')
plt.xlabel('')
plt.ylabel('Erro quadrático')
plt.show()
print("\n")

# Validação do modelo
## Calcule a precisão dos dados de teste
n_records, n_features = X_test.shape
predictions=0

for xi, yi in zip(X_test.values, y_test.values):
  # ----- Forward Pass -----
  ## Camada oculta
  hidden_layer_input = np.dot(xi, weights_input_hidden) # Calcule a combinação linear de entradas e pesos sinápticos
  hidden_layer_output = sigmoid(hidden_layer_input)     # Aplicado a função de ativação

  ## Camada de Saída
  output_layer_in = np.dot(hidden_layer_output, weights_hidden_output) # Calcule a combinação linear de entradas e pesos sinápticos

  ## Aplicado a função de ativação 
  output = sigmoid(output_layer_in)

  ## Cálculo do Erro da Predição
  if (output[0]>output[1]):
    if (yi[0]>yi[1]):
      predictions+=1
                
  if (output[1]>=output[0]):
    if (yi[1]>yi[0]):
      predictions+=1

print("\n")
print("Acurácia da predição: {:.3f}".format(predictions/n_records))
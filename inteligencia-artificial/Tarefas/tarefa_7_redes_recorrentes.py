# Importando bibliotecas

import pandas as pd
from keras.models import Sequential
from keras.layers import Dense, Dropout, LSTM
import plotly.graph_objects as go
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.preprocessing import MinMaxScaler
%matplotlib inline

# Carregando os dados
DataSet = pd.read_csv('Futuros Mini Ibovespa - teste.csv')
fig = go.Figure( data = [
  go.Candlestick(
    x     = DataSet['Date'],
    open  = DataSet['Open'],
    high  = DataSet['High'],
    low   = DataSet['Low'],
    close = DataSet['Close']
  )
])

fig.update_layout( xaxis_rangeslider_visible = False )
fig.show()

# Agora vamos ler o arquivo do período desejável
DataSet = pd.read_csv('Futuros Mini Ibovespa - treino.csv')
DataSet = DataSet.dropna()
DataSet.head()
DataSet.describe()

# Inicialmente iremos criar uma RNN baseada apenas no Valor de Abertura
plt.scatter( DataSet['Date'], DataSet['Open'] )
plt.show()
base_treinamento = DataSet.iloc[:, 1:2].values

# Normalizar os dados do Mini Índice
scaler = MinMaxScaler( feature_range = (0,1) )
DataScaled = scaler.fit_transform(base_treinamento)

# Definição dos previsores
previsores = []
preco_real = []
NRecursao = 90
DataSetLen = len(DataScaled)
print(DataSetLen)

for i in range(NRecursao, DataSetLen):
  previsores.append( DataScaled[i-NRecursao:i,0] )
  preco_real.append( DataScaled[i,0] )

previsores, preco_real = np.array(previsores), np.array(preco_real)

# Tranformar para o formato do Tensor do Keras
previsores = np.reshape(previsores, (previsores.shape[0], previsores.shape[1], 1))

# Estrutura da Rede Neural
regressor = Sequential()                                 # Camada de entrada
regressor.add(LSTM(units = 100, return_sequences = True, input_shape = (previsores.shape[1], 1)))
regressor.add(Dropout(0.3))

regressor.add(LSTM(units = 50, return_sequences = True)) # Cada Oculta 1
regressor.add(Dropout(0.3))

regressor.add(LSTM(units = 50, return_sequences = True)) # Cada Oculta 2
regressor.add(Dropout(0.3))

regressor.add(LSTM(units = 50))                          # Cada Oculta 3
regressor.add(Dropout(0.3))

regressor.add(Dense(units = 1, activation = 'linear'))   # Camada de Saída

# Construindo a Rede
regressor.compile(
  optimizer = 'rmsprop',
  loss = 'mean_squared_error',
  metrics = ['mean_absolute_error']
)
regressor.fit(previsores, preco_real, epochs = 20, batch_size = 32)

# Conjunto de dados para o Teste
DataSet_teste = pd.read_csv('Futuros Mini Ibovespa - teste.csv')
preco_real_teste = DataSet_teste.iloc[:, 1:2].values
base_completa = pd.concat((DataSet['Open'], DataSet_teste['Open']), axis = 0)
entradas = base_completa[len(base_completa) - len(DataSet_teste) - NRecursao:].values
entradas = entradas.reshape(-1, 1)
entradas = scaler.transform(entradas)

DataSetTestLen = len(DataSet_teste)
NPredictions = 90
X_teste = []
for i in range(NRecursao, DataSetTestLen + NRecursao):
  X_teste.append(entradas[i-NRecursao:i, 0])

X_teste = np.array(X_teste)
X_teste = np.reshape(X_teste, (X_teste.shape[0], X_teste.shape[1], 1))

previsoes = regressor.predict(X_teste)
previsoes = scaler.inverse_transform(previsoes)

RNN = []
predictions_teste = X_teste[0].T
predictions_teste = np.reshape(predictions_teste, (predictions_teste.shape[0], predictions_teste.shape[1], 1))

predictions_teste[0][NRecursao-1][0] = regressor.predict(predictions_teste)[0][0]
RNN.append(regressor.predict(predictions_teste)[0])

for i in range(NPredictions-1):
  predictions_teste = np.roll(predictions_teste,-1)
  predictions_teste[0][NRecursao-1][0] = regressor.predict(predictions_teste)[0][0]
  RNN.append(regressor.predict(predictions_teste)[0])

RNN = scaler.inverse_transform(RNN)

print(RNN.mean())
print(previsoes.mean())
print(preco_real_teste.mean())

plt.plot(
  preco_real_teste,
  color = 'red',
  label = 'Preço real'
)
plt.plot(
  previsoes,
  color = 'blue',
  label = 'Previsões'
)

plt.title('IBOBESPA')
plt.xlabel('Tempo')
plt.ylabel('Valor')
plt.legend()
plt.show()

np.shape(previsoes)
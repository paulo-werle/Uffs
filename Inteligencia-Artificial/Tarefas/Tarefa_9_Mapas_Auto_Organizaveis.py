# Importando as bibliotecas
from minisom import MiniSom
import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from matplotlib.pylab import pcolor, colorbar, plot, plt
import matplotlib.patches as mpatches

# Carregando os dados
base = pd.read_csv('wines.csv')
base.head()
base.describe()

# Camada de entrada e rótulos para validação
X = base.iloc[:,1:14].values
y = base.iloc[:,0].values

# Normalização dos dados
normalizador = MinMaxScaler(feature_range = (0,1))
X = normalizador.fit_transform(X)

# Construção do SOM
som = MiniSom(x = 10, y = 10, input_len = 13, sigma = 1.0, learning_rate = 0.9, random_seed = 2)
som.random_weights_init(X)
som.train_random(data = X, num_iteration = 100000)

# Topologia da Rede
som._activation_map

# Pesos do SOM
som._weights

# Visualização de quantas vezes determinado neurônio foi ativado
q = som.activation_response(X)
q

# MID - distância média entre neurônios
pcolor(som.distance_map().T)
colorbar()

# Regiões de ativação (classe)
markers = ['o', 's', 'D']
color = ['r', 'g', 'b']
y[y == 1] = 0
y[y == 2] = 1
y[y == 3] = 2

for i, x in enumerate(X):
  w = som.winner(x)
  plot(
    w[0] + 0.5,
    w[1] + 0.5,
    markers[y[i]],
    markerfacecolor = 'None',
    markersize = 10,
    markeredgecolor = color[y[i]],
    markeredgewidth = 2
  )

w = som.winner( X[148] )
print(w)


red_patch = mpatches.Patch(color = 'red', label = 'Class_3')
blue_patch = mpatches.Patch(color = 'blue', label = 'Class_1')
green_patch = mpatches.Patch(color = 'green', label = 'Class_2')


plt.figure(figsize = (8,5))
plt.title('SOM')
plt.pcolor(som.distance_map().T) # distance map as background
plt.colorbar()

for cnt,xx in enumerate(X):
  w = som.winner(xx)
  plt.plot(
    w[0]+.5,
    w[1]+.5,
    markers[y[cnt]],
    markerfacecolor = 'None',
    markeredgecolor = color[y[cnt]],
    markersize = 12,
    markeredgewidth = 2
  )

plt.axis([0, som.get_weights().shape[0], 0, som.get_weights().shape[1] ])
plt.legend(handles = [red_patch, blue_patch,green_patch])
plt.show()
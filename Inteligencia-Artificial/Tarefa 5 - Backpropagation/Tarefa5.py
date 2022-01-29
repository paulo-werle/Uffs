# Configuração da MPL - Importando a biblioteca
import numpy as np

# Configuração da MPL - Função do cáculo da sigmóide
def sigmoid(x):
    return 1/(1+np.exp(-x))

# Configuração da MPL - Arquitetura da MPL
N_input = 3
N_hidden = 4
N_output = 2

# Configuração da MPL - Vetor dos valores de entrada
x = np.array([0.5, 0.1, -0.2])
target = np.array([0.3, 0.8])
learnrate = 0.5

# Configuração da MPL - Pesos da Camada Oculta
weights_input_hidden = np.array([[-0.08,  0.08, -0.03, 0.03],
                                 [ 0.05,  0.10,  0.07, 0.02],
                                 [-0.07,  0.04, -0.01, 0.01]])

# Configuração da MPL - Pesos da Camada de Saída
weights_hidden_output = np.array([[-0.18,  0.11],
                                  [-0.09,  0.05],
                                  [-0.04,  0.05],
                                  [-0.02,  0.07]])

# Forward Pass
# Camada oculta - Calcule a combinação linear de entradas e pesos sinápticos
hidden_layer_input = np.dot(x, weights_input_hidden)

# Camada oculta - Aplicado a função de ativação
hidden_layer_output = sigmoid(hidden_layer_input)

# Camada de Saída - Calcule a combinação linear de entradas e pesos sinápticos
output_layer_in = np.dot(hidden_layer_output, weights_hidden_output)

# Camada de Saída - Aplicado a função de ativação 
output = sigmoid(output_layer_in)

# Backward Pass
error = target - output                                                             # TODO: Cálculo do Erro
output_error_term = error * output * (1 - output)                                   # TODO: Calcule o termo de erro de saída (Gradiente da Camada de Saída)
hidden_error = np.dot(weights_hidden_output,output_error_term)                      # TODO: Calcule a contribuição da camada oculta para o erro
hidden_error_term = hidden_error * hidden_layer_output * (1 - hidden_layer_output)  # TODO: Calcule o termo de erro da camada oculta (Gradiente da Camada Oculta)
delta_w_h_o = learnrate * output_error_term*hidden_layer_output[:, None]            # TODO: Calcule a variação do peso da camada de saída
delta_w_i_h = learnrate * hidden_error_term * x[:, None]                            # TODO: Calcule a variação do peso da camada oculta

print('delta_w_h_o: ',delta_w_h_o)
print('delta_w_i_h: ',delta_w_i_h)

# Atualização dos Pesos
weights_input_hidden = learnrate * delta_w_i_h
print('weights_input_hidden: ',weights_input_hidden)

weights_hidden_output = learnrate * delta_w_h_o
print('weights_hidden_output: ',weights_hidden_output)
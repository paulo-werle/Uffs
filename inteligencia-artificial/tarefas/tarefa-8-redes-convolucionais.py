# Importando as bibliotecas
from keras.models import Sequential
from keras.layers import Conv2D, MaxPooling2D, Flatten, Dense, Dropout
from keras.layers.normalization import BatchNormalization
from keras.preprocessing.image import ImageDataGenerator
import numpy as np
from keras.preprocessing import image

# Arquitetura da Rede Convolucional
classificador = Sequential()
classificador.add( Conv2D(
  32,
  (3, 3),
  activation='relu',
  kernel_initializer='he_uniform',
  padding='same',
  input_shape=(224, 224, 3)
))
classificador.add( BatchNormalization() )
classificador.add( MaxPooling2D((2, 2)) )
classificador.add( Dropout(0.2) )

classificador.add( Conv2D(
  64,
  (3, 3),
  activation='relu',
  kernel_initializer='he_uniform',
  padding='same'
))
classificador.add( BatchNormalization() )
classificador.add( MaxPooling2D((2, 2)) )
classificador.add( Dropout(0.25) )

classificador.add( Conv2D(
  128,
  (3, 3),
  activation='relu',
  kernel_initializer='he_uniform',
  padding='same'
))
classificador.add( BatchNormalization() )
classificador.add( MaxPooling2D((2, 2)) )
classificador.add( Dropout(0.3) )

classificador.add( Flatten() )
classificador.add( Dense(
  1024,
  activation='relu',
  kernel_initializer='he_uniform'
))
classificador.add( BatchNormalization() )
classificador.add( Dropout(0.35) )
classificador.add( Dense(
  128,
  activation='relu',
  kernel_initializer='he_uniform'
))
classificador.add( BatchNormalization() )
classificador.add( Dropout(0.4) )
classificador.add( Dense(
  2,
  activation='relu',
  kernel_initializer='he_uniform'
))
classificador.add( BatchNormalization() )
classificador.add( Dropout(0.5) )
classificador.add( Dense(
  1,
  activation='sigmoid'
))

classificador.compile(
  optimizer = 'adam',
  loss = 'binary_crossentropy',
  metrics = ['accuracy']
)

# Normalizar as imagens
gerador_treinamento = ImageDataGenerator(
  rescale = 1./255,
  rotation_range = 7,
  horizontal_flip = True,
  shear_range = 0.2,
  height_shift_range = 0.07,
  zoom_range = 0.2
)
gerador_teste = ImageDataGenerator(rescale = 1./255)

base_treinamento = gerador_treinamento.flow_from_directory(
  'dataset/training_set',
  target_size = (224, 224),
  batch_size = 64,
  class_mode = 'binary'
)

base_teste = gerador_teste.flow_from_directory(
  'dataset/test_set',
  target_size = (224, 224),
  batch_size = 64,
  class_mode = 'binary'
)
classificador.summary()

# Treinamento
classificador.fit_generator(
  base_treinamento,
  steps_per_epoch = 40,
  epochs = 10,
  validation_data = base_teste,
  validation_steps = 10
)

# Teste
imagem_teste = image.load_img(
  'dataset/test_set/cachorro/dog.3969.jpg',
  target_size = (224,224)
)
imagem_teste

imagem_teste = image.img_to_array(imagem_teste)
imagem_teste /= 255
imagem_teste = np.expand_dims(imagem_teste, axis = 0)

previsao = classificador.predict(imagem_teste)
previsao
base_treinamento.class_indices
previsao = (previsao > 0.5)
previsao
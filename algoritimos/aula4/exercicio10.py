'''Faça um programa que receba um número inteiro que representa uma quantidade em segundos.
A saída do programa é o equivalente dessa quantidade em dias, horas, minutos e segundos. A ideia é
fazer um programa que calcule quanto tempo alguém esperou pelo ônibus, por exemplo: se o
usuário cronometrar o tempo em segundos que esperou e depois passar para o programa, ele irá
informar algo do tipo: Você esperou 0 dias, 0 horas, 40 minutos e 13 segundos.
Ex.:
Entrada 124, saída: Você esperou 0 dias, 0 horas, 2 minutos e 4 segundos
Entrada 194403, saída: Você esperou 2 dias, 6 horas, 0 minutos e 3 segundos'''

segundos = int(input("Digite a quantidade de Segundos que vc esperou para pegar o ônibis:  "))

import math

minutos = segundos // 60
segundos = segundos % 60

horas = minutos // 60
minutos = minutos % 60

dias = horas // 24
horas = horas % 24


print("Voce esperou: ",dias, "dias ",horas ,"horas ",minutos , "minutos e ",segundos ,"segundos")





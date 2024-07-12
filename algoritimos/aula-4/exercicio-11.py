# Descrição:
'''Faça um programa que faça o processo inverso da questão 10. Ele recebe como entradas a
quantidade de dias, horas, minutos e segundos e, como saída, mostra quanto esse tempo equivale
em segundos.'''

dias = int(input("Informe a quantidade de dias :  "))
horas = int(input("Informe a quantidade de horas :  "))
minutos = int(input("Informe a quantidade de minutos :  "))
segundos = int(input("Informe a quantidade de segundos :  "))

import math

dias = dias * 24 * 60 * 60
horas = horas * 60 *60
minutos = minutos * 60
segundos = segundos + minutos + horas + dias


print("Voce esperou ",segundos , "segundos")

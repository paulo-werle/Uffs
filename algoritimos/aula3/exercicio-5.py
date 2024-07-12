'''Elabore um programa que leia as variáveis a, b e c de uma equação de segundo grau e em
seguida, calcule suas raizes utilizando a fórmula de Bhaskara. Caso o delta for negativo, imprimir
mensagem que a equação não possui raízes que pertencem aos número reais. Caso contrário,
imprimir as raizes encontradas.'''

import math

a = int(input("Informe o Valor de A  "))
b = int(input("Informe o Valor de B  "))
c = int(input("Informe o Valor de C  "))

delta = (b**2)-(4*a*c)

if delta<0:
	print("A equação não possui raízes que pertencem aos número reais")
else:
	raiz1 = (-b - math.sqrt(delta))/(2*a)
	raiz2 = (-b + math.sqrt(delta))/(2*a)
	print("X¹:", raiz1, "X²", raiz2)

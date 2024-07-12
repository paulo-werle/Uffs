# Descrição:
'''Faça um programa que receba três números inteiros e informe qual deles é o maior e qual deles é
o menor.'''

n1 = int(input("Informe o Primeiro Numero  "))
n2 = int(input("Informe o Segundo Numero  "))
n3 = int(input("Informe o Terceiro Numero  "))

if (n1 != n2) and (n1 != n3) and (n2 != n3):

	if(n1>n2)and(n1>n3):
		print("O Maior numero é: ", n1)

	elif(n2>n1)and(n2>n3):
		print("O Maior numero é: ", n2)

	elif(n3>n1)and(n3>n2):
		print("O Maior numero é: ", n3)

elif (n1==n2) or (n1==n3) or (n2==n3):
	if n1==n2:
		print("O Maior numero é: ", n1)

	elif n1==n3:
		print("O Maior numero é: ", n1)

	elif n2==n3:
		print("O Maior numero é: ", n2)

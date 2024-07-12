# Descrição:
'''Faça um programa que leia um número N e imprima “F1”, “F2” ou “F3”, conforme a condição:
• “F1”, se N <= 10
• “F2”, se N > 10 e N <= 100
• “F3”, se n > 100
Obs.: utilizar condições com elif.'''

n = float(input("Informe o Valor de A  "))

if n <= 10:
	print("F1")

elif (n > 10) and (n <= 100):
	print("F2")

elif n > 100:
	print("F3")

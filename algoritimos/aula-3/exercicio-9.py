# Descrição:
'''Faça um algoritmo que leia um número N e imprima “F1”, “F2” ou “F3”, conforme a condição:
• “F1”, se n <= 10
• “F2”, se n > 10 e N <= 100
• “F3”, se n > 100'''

n = float(input("Informe o Valor de A  "))

if n <= 10:
	print("F1")

elif (n > 10) and (n <= 100):
	print("F2")

elif n > 100:
	print("F3")


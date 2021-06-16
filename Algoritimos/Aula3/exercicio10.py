'''Faça um programa que receba três números inteiros. A saída do programa é o maior número
ímpar digitado pelo usuário. Caso nenhum número ímpar tenha sido informado, imprimir
mensagem informando que nenhum número ímpar foi informado. Dica: utilizar variável boolean.'''

n1 = int(input("Informe o Primeiro Numero  "))
n2 = int(input("Informe o Segundo Numero  "))
n3 = int(input("Informe o Terceiro Numero  "))

if (n1%2 == 1) or (n2%2 == 1) or (n3%2 == 1):
	
	maior = -10000000
	if (n1%2 == 1) and n1>maior:
		maior = n1
		
	if (n2%2 == 1) and n2>maior:
		maior = n2
		
	if (n3%2 == 1) and n3>maior:
		maior = n3
	print("O maior Numero Impar é: ", maior)
			
else:
	print("Nenhum numero impar informado")
		

# Descrição:
'''Faça um programa que leia um número inteiro e retorne uma mensagem indicando se o número é
par ou ímpar, e se é positivo ou negativo. Obs.: considere que o usuário irá digitar corretamente o
número inteiro.'''

n = int(input("Digite um numero Inteiro "))

if n%2 == 1:
	print("O Numero é INPAR")
else:
	print("O Numero é PAR")

if n>=0:
	print("O Numero é POSITIVO")
else:
	print("O Numero é NEGATIVO")

# Descrição:
'''Faça um programa que leia quatro números (Opção , Num1 , Num2 e Num3) e mostre o valor de
Num1 se Opção for igual a 2; o valor de Num2 se Opção for igual a 3; e o valor de Num3 se Opção
for igual a 4. Os únicos valores possíveis para a variável Opção são 2, 3 e 4. Caso seja digitada uma
operação diferente, o programa deve mostrar a mensagem “Opção inválida” antes de ler os três
números.'''

import os

Opcao = int(input("Digite a Opção Desejada "))

if Opcao == 2:
	Num1 = float(input("Digite Um Numero "))
	os.system("cls")
	print("O Numero digitado foi : ", Num1)

elif Opcao == 3:
	Num2 = float(input("Digite um Numero "))
	os.system("cls")
	print("O Numero digitado foi : ", Num2)

elif Opcao == 4:
	Num3 = float(input("Digite um Numero "))
	os.system("cls")
	print("O Numero digitado foi : ", Num3)

else:
	print("Opção inválida")


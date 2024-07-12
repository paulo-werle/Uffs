# Descrição:
'''Escrever um programa para ler dois números. Se os números forem iguais imprimir a mensagem:
“Números iguais” e encerrar a execução; caso contrário, imprimir o de maior valor, acompanhado
pela mensagem “é o maior número”. Obs.: utilizar condições com elif.'''

n1 = int(input("Informe o primeiro Numero "))
n2 = int(input("Informe o segundo Numero "))

if n1==n2:
	print("Números iguais")

elif n1>n2:
	print(n1,"é o maior número")

else:
	print(n2,"é o maior número")

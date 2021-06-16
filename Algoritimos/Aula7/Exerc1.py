''' Faça um programa que leia um numero inteiro até que o usuario informe o valor 0. Para cada numero lido, informe seu antecessor e seu sucessor. O termino do laço deve ser feito com o comando BREAK'''

while True:
	n = int(input("Informe um Valor: "))
	
	if n == 0:
		break
	else:
		print("Sucessor: {},Antecessor: {}".format(n+1,n-1))

'''Leia 10 números, e para cada um mostre seu sucessor e seu antecessor na tela. Utilizar laço FOR.'''

for num in range(10):
	n = int(input("Digite um Numero: "))
	antecessor = n - 1
	sucessor = n + 1
	print("O numero: {}, tem como antecessor: {}, e como sucessor: {}".format(n,antecessor,sucessor))

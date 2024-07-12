# Descrição:
'''Leia 10 números, e para cada um mostre seu sucessor e seu antecessor na tela.'''

n = 1

while n < 10:
	numero = int(input("Digite um Numero"))
	print("Seu sucesor é: ",numero+1)
	print("Seu antesecesor é: ",numero-1)

	n += 1


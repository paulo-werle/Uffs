'''Escreva um programa que leia um valor N inteiro e calcule o fatorial deste número.'''

numero = int(input("Informe um valor: "))
resultado = 1
cont = 0

for num in range(numero):
	cont += 1
	resultado = resultado * cont
	
print("O fatorial de : {} é : {}".format(numero,resultado))

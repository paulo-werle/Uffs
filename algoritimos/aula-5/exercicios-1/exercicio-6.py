# Descrição:
'''Escreva um programa que leia um valor N inteiro e calcule o fatorial deste número.'''

fat = int(input("Informe um valor para ser fatorado "))
cont = fat - 1
resultado = fat

while cont > 0:
	resultado = resultado * cont
	cont = cont-1

print("O fatorial de {} é igual a {}".format(fat,resultado))

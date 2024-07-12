# Descrição:
'''Faça um programa que receba números até que o usuário digite 0. Em seguida, mostre na tela a
soma dos números pares e a soma dos números ímpares informados. Ex: se o usuário informar 2, 3,
6, 9 e 0, o programa mostra como saída: Soma dos pares: 8, Soma dos impares: 12.'''

numero = int(input("Digite numeros impares e pares, ou digite 0 para sair "))
par = 0
impar = 0

while numero != 0:

	if numero%2 == 1:
		impar = impar + numero
	else:
		par = par + numero

	numero = int(input("Digite numeros impares e pares, ou digite 0 para sair "))

print("Soma dos pares: {}, Soma dos impares: {}.".format(par,impar))

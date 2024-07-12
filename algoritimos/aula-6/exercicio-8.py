'''Faça um programa que some todos os números abaixo de 1000 que são múltiplos de 3 ou 5.'''

resultado = 0

for num in range(1000):

	if num%3 == 0 or num%5 == 0:
		resultado = resultado + num
		
print(resultado)

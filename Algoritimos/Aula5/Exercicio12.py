'''Faça um programa que receba um número inteiro e diga se ele é perfeito. Um número perfeito é
aquele cuja soma de todos os seus divisores é igual a ele mesmo. Ex.: 6 porque 1 + 2 + 3 = 6; 28
porque 1 + 2 + 4 + 7 + 14 = 28. Lembrando: um divisor é um número que ao ser utilizado para uma
divisão resulta em um número exato.'''

n = int(input("Infome um Numero para vereficar se ele é Perfeito "))
soma = 0
aux = n - 1

while aux > 0:
	
	if n%aux ==0:
		soma += aux
		
	aux -= 1
	
if soma==n:
		print("O numero {} é Perfeito".format(n))
else:
		print("O numero {} não é Perfeito".format(n))

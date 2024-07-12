'''Faça um programa que leia 20 números para uma lista. A seguir, verifique e remova todos os
números que não são pares. Por fim, escreva o vetor com as modificações realizadas.'''

#Leitura dos números
numeros = []
for i in range(5):
	n = int(input("Informe o N{}: ".format(i+1)))
	numeros.append(n)
	
#Remove os número não pares
for n in numeros:
	if n % 2 != 0:
		numeros.remove(n)
	
print()
print(numeros)

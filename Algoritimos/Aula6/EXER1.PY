'''Escreva um programa usando FOR que leia 5 valores e mostre a soma entre o maior e menor deles'''

valor = int(input("Informe um Valor"))

maior = valor
menor = valor

for num in range(4):
	valor = int(input("Informe um Valor"))
	
	if valor > maior:
		maior = valor
	elif valor < menor:
		menor = valor
		
soma = maior + menor
		
print ("A soma entre o maior e o menor numero é:{}".format(soma))

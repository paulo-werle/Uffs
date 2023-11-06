'''Chico tem 1,50 metros e cresce 2 centímetros por ano, enquanto Zé tem 1,18 metros e cresce 4
centímetros por ano. Construa um algoritmo que calcule e imprima quantos anos serão necessários
para que Zé seja maior que Chico.'''

chico = 1.50
ze = 1.18
ano = 0

while chico > ze:
	if chico > ze:
		chico += 0.02
		ze += 0.04
		ano+=1
		
print("Serao necessarios {} anos para que Zé seja maior que Chico".format(ano))

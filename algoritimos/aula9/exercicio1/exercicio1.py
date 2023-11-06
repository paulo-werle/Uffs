'''Faça um programa que leia numeros interiros para uma matriz 4x4. 
Em seguida, calcule a média dos elementos dessa matrix. '''

matriz=[]
for i in range(4):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(4):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)
	
	
soma=0
for i in range(4):
	for j in range(4):
		soma+=matriz[i][j]
		media= soma/16

print("\n A Media dos Numeros é ",media)
	

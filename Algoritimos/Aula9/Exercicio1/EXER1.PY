'''Faça um programa que leia uma matriz 4 x 4. Após, imprima na tela a soma dos elementos que
estão abaixo da diagonal principal da matriz.'''

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
		if i > j:
			soma+=matriz[i][j]

print("\n A Soma dos Numeros é ",soma)





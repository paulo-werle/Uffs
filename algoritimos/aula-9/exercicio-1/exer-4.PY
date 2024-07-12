'''Faça um programa que leia uma matriz 5 x 5. Em seguida, percorra a matriz e imprima apenas os
números pares.'''

matriz=[]
for i in range(5):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(5):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)

for i in range(5):
	for j in range(5):
		if matriz[i][j]%2==0:
			print(matriz[i][j],end=" ")
		else:
			print(end="  ")
	print()

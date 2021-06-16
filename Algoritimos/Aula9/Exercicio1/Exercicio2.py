'''Faça um programa igual ao anterior, porem escreva os elemtnros da diagonal 
principal e em seguida, imprima a soma deles'''

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
		if i == j:
			soma+=matriz[i][j]

print("\n A Soma dos Numeros é ",soma)

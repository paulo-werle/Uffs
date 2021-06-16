matriz=[]
for i in range(4):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(4):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)

for i in range(4):
	for j in range(4):
		print(matriz[i][j],end=" ")
	print()

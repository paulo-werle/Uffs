'''Faça um programa para ler e somar duas matrizes 5 x 4 (matriz A e matriz B). A soma deve ser
realizada na função soma_matriz(matA, matB), sendo que a mesma deverá retornar uma nova
matriz contendo o resultado da soma. Por fim, deve-se imprimir a matriz retornada pela função no
código principal do programa.'''

#FUNÇÃO
def soma_matriz(matA,matB):
	
	matriztotal=[]

	for i in range(5):
		linha=[]
		for j in range(4):
			valor= matA[i][j] + matB[i][j]
			linha.append(valor)
		matriztotal.append(linha)
			
	return matriztotal
	

#CODIGO PRICIPAL
matriza=[]

print("\n Informe o Valor para colocar na Matriz \n")
for i in range(5):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(4):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriza.append(linha)
	
matrizb=[]

print("\n Informe o Valor para colocar na Matriz \n")
for i in range(5):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(4):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matrizb.append(linha)
	
matrizc = soma_matriz(matriza,matrizb)
print()

for i in range(5):
	for j in range(4):
		print(matrizc[i][j],end=" ")
	print()

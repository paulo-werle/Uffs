'''Faça um programa igual ao exercício 2. Porém, a leitura das matrizes deve ser realizada
utilizando uma função que deve ser chamada duas vezes, uma para a matriz A e outra para a matriz
B. Além disso, a impressão da soma das matrizes A e B também deve ser realizada em uma função'''

#FUNÇÃO
def ler_matriz():
	matriz=[]

	print("\n Informe o Valor para colocar na Matriz \n")
	for i in range(5):
		linha=[]
		print("Informe o Valor para colocar na {} Linha".format(i+1))
		for j in range(4):
			valor= int(input("{}º:  ".format(j+1)))
			linha.append(valor)
		matriz.append(linha)
		
	return matriz
		
def soma_matriz(matA,matB):
	
	matriztotal=[]

	for i in range(5):
		linha=[]
		for j in range(4):
			valor= matA[i][j] + matB[i][j]
			linha.append(valor)
		matriztotal.append(linha)
			
	return matriztotal
	
def imprime_matriz(c):
	for i in range(5):
		for j in range(4):
			print(c[i][j],end=" ")
		print()
		
#CODIGO PRINCIPAL

a = ler_matriz()
b = ler_matriz()

c = soma_matriz(a,b)

imprime_matriz(c)



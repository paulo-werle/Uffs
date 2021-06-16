'''Faça um programa que leia uma matriz quadrada de tamanho (ordem) 4. Depois, multiplique essa
matriz por um número dentro de uma função, sendo esse número também lido pelo usuário. Por
fim, imprima a matriz com os números já multiplicados.'''

#FUNÇÃO
def ler_matriz():
	
	matriz=[]
	print("\n Informe o Valor para colocar na Matriz \n")
	for i in range(4):
		linha=[]
		print("Informe o Valor para colocar na {} Linha".format(i+1))
		for j in range(4):
			valor= int(input("{}º:  ".format(j+1)))
			linha.append(valor)
		matriz.append(linha)
	
	return matriz

def ler_mux():
	
	mux = input("Informe o valor pelo qual devo multiplicar a matriz: ")

	return mux
	
def multiplicador(matriz,mux):
	for i in range(4):
		for j in range(4):
			matriz[i][j] = matriz[i][j] * mux
			
	return matriz

def imprimir(matriz):
	for i in range(4):
		for j in range(4):
			print(matriz[i][j],end=" ")
		print()
#CODIGO PRINCIPAL

matriz = ler_matriz
mux = ler_mux
matriz = multiplicador(matriz,mux)
imprimir()


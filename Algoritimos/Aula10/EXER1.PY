'''Faça um programa que leia a ordem (tamanho de linhas e colunas) de uma matriz quadrada. Em
seguida, leia números para os elementos desta matriz. Por fim, especifique a função
imprime_matriz(matriz, ordem), que deverá imprimir todos os elementos da matriz recebida por
parâmetro.'''

#FUNÇÃO
def imprime_matriz(matriz, ordem):
	for i in range(ordem):
		for j in range(ordem):
			print(matriz[i][j],end=" ")
		print()

#CODIGO PRINCIPAL
ordem = int(input("Informe o tamanho de Linhas que deseja na Matriz "))
matriz=[]

print("\n Informe o Valor para colocar na Matriz \n")
for i in range(ordem):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(ordem):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)
	
print()
imprime_matriz(matriz,ordem)
	

	


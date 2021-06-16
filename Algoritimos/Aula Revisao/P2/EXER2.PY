'''Faça um programa que leia uma matriz 4 x 3, multiplique cada elemento desta matriz por 2, e
imprima a matriz multiplicada. Atenção: a leitura e impressão da matriz devem ser realizadas em
uma função.'''

#FUNÇÕES
def ler_matriz():
	matriz = [ ]
	for i in range(3 ):
		linha = [ ]
		for j in range(4 ):
			valor = int(input("Informe um valor"))
			linha.append(valor)
		matriz.append(linha)

	return matriz

def mux(matriz):
	for i in range (3):
		for j in range(4):
			matriz[i][j] = matriz[i][j] * 2

	for i in range (3):
		for j in range(4):
			print( " {}".format(matriz[i][j]),end = " ")
		print()

#CODIGO PRINCIPAL
matriz = ler_matriz()
mux(matriz)

'''Faça um programa para ler e somar duas matrizes 5 x 4 (matriz A e matriz B). O resultado da
soma deve ser guardado em uma matriz C, sendo que a mesma deverá ser impressa no final do
programa.'''

matriz1=[]
print("\n Informe o Valor para colocar na 1ª Matriz \n")
for i in range(4):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(5):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz1.append(linha)
	
matriz2=[]
print("\n Informe o Valor para colocar na 2ª Matriz \n")
for i in range(4):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(5):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz2.append(linha)
	
matriz3=[]
for i in range(4):
	linha=[]
	for j in range(5):
		soma = matriz1[i][j] + matriz2[i][j]
		linha.append(soma)
	matriz3.append(linha)
	
for i in range(4):
	for j in range(5):
		print(matriz3[i][j],end=" ")
	print()
		

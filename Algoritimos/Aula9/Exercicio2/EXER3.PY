'''Faça um programa que leia uma matriz 5x5. Em seguida, crie 2 vetores (SL e SC) de 5 elementos
que contenham respectivamente as somas das linhas e das colunas da matriz. Por exemplo, a
posição 0 do vetor SL deve armazenar a soma dos elementos da linha 0 da matriz. A posição 3 do
vetor SC deve armazenar a soma dos elementos da coluna 3 da matriz. Por fim, imprima os vetores
criados.'''

matriz=[]

print("\n Informe o Valor para colocar na Matriz \n")
for i in range(5):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(5):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)
	
for i in range(5):
	for j in range(5):
		print(matriz[i][j],end=" ")
	print()
	
sl=[]
sc=[]
somatotal = 0

for i in range(5):
	cont=0
	somacoluna=0
	
	for i in range(5):
		somacoluna += matriz[i][cont]
		somatotal = somacoluna
		
	sc.append(somatotal)
	cont+=1

print()
for i in range(5):
	print(sc[i],end=" ")
	
for i in range(5):
	cont=0
	somalinha=0
	for i in range(5):
		somalinha += matriz[cont][i]
		somatotal = somalinha
		
	sl.append(somatotal)
	cont+=1

print()
for i in range(5):
	print(sl[i],end=" ")

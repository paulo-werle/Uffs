'''Dada a mesma matriz do exercício 5, exclua as linhas que possuem o elemento da primeira
coluna sendo par.'''

matriz=[[1,8,3,22,30],[21,12,9,16,31],[14,7,5,8,19],[10,25,24,4,9],[5,18,16,26,20]]
cont=5

for i in range(5):
	if matriz[i][0]%2==0:
		matriz.pop(i)
		cont-=1
		
for i in range(cont):
	for j in range(5):
		print(matriz[i][j],end=" ")
	print()

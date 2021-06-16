'''Escreva um programa que leia uma matriz 5 x 5 e calcule as somas:
a) de todos os elementos da linha 4;
b) de todos os elementos da coluna 2;
c) da diagonal secundária;
d) de todos os elementos da matriz.'''

matrix=[]
for i in range(5):
	linha=[]
	print("Informe o Valor para colocar na {} Matrix".format(i+1))
	for j in range(5):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matrix.append(linha)

a=0
b=0
c=0
d=0

for i in range(5):
	for j in range(5):
		if i == 3:
			a+=matrix[i][j]
			
		if j == 1:
			b+=matrix[i][j]
			
		if i+j == 4:
			c+=matrix[i][j]
			
		d+=matrix[i][j]

print('''A soma de todos os elementos da linha 4; {}
A soma de todos os elementos da coluna 2; {}
A somada diagonal secundária; {}
A somade todos os elementos da matriz; {}'''.format(a,b,c,d))

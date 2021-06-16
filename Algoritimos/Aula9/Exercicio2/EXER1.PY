'''Faça um programa que leia uma matriz 4x4 e calcule as somas dos elementos marcados com o X.
Utilize estruturas de repetição.
a)      b)      c)      d)
XX..    ....    X...    .XXX
XX..    ....    XX..    ..XX
....    ..XX    XXX.    ...X
....    ..XX    XXXX    ....'''

matriz=[]

print("\n Informe o Valor para colocar na Matriz \n")
for i in range(4):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(4):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)
	
a = 0
b = 0
c = 0
d = 0

for i in range(4):
	for j in range(4):
		
		if j <= 1 and i <= 1:
			a += matriz[i][j]
			
		if j >= 2 and i >= 2:
			b += matriz[i][j]
			
		if j <= i :
			c += matriz[i][j]
			
		if j > i :
			d += matriz[i][j]
			
print()
print("O Resultado da a) é: ",a)
print("O Resultado da b) é: ",b)
print("O Resultado da c) é: ",c)
print("O Resultado da d) é: ",d)			
		

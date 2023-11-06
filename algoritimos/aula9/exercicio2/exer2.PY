'''Faça um programa que leia uma matriz 5x5. Em seguida, leia um número N e escreva em quais
posições da matriz (linha e coluna) o valor de N foi encontrado. Caso N não exista na matriz,
imprima uma mensagem informando isso.'''

matriz=[]

print("\n Informe o Valor para colocar na Matriz \n")
for i in range(5):
	linha=[]
	print("Informe o Valor para colocar na {} Linha".format(i+1))
	for j in range(5):
		valor= int(input("{}º:  ".format(j+1)))
		linha.append(valor)
	matriz.append(linha)
	
n = int(input("Informe um valor para N "))
imprimir=0

for i in range(5):
	for j in range(5):
		if n == matriz[i][j]:
			print("Foi encontrado o Valor:{}, nas seguinte linha:{} e coluna:{}".format(n,i+1,j+1))
			imprimir+=1
			
if imprimir == 0:
	print("Nao existe o valor N na matriz")
	


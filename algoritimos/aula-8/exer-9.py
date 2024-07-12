'''Leia uma lista de inteiros com 15 posições e acumule os valores do primeiro elemento no
segundo, deste no terceiro e assim por diante. Ao final, escrever os elementos obtidos.'''

x=[]
cont=0

for num in range(15):
	numero = int(input("Informe o {}º ".format(num+1)))
	cont+= numero
	
	x.append(cont)

print(x)

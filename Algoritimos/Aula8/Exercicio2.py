#Faça um Programa que lê cinco (5) nomes digitados pelo usuario e no final imprime esses nomes ordenados. 
#Guarde os nomes em uma lista para serem ordenados no final

'''i = []

for num in range(5):
	nome=input("Informe o Nome: ")
	i.append(nome)
	
for cont in range(5):
	print(i[cont],end=", ")'''
	
#Faça um Programa que lê cinco (5) nomes digitados pelo usuario e no final imprime esses nomes ordenados. 
#Guarde os nomes em uma lista para serem ordenados no final

i = []
num = 0
cont = 0

while num < 5:
	nome=input("Informe o Nome: ")
	i.append(nome)
	num+= 1
	
while cont < 5:
	print(i[cont],end=", ")
	cont+=1

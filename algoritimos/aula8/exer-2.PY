'''Escreva um programa que leia 10 palavras com um laço FOR, armazenando-as em uma lista. Ao
final, deve-se imprimir qual foi a palavra digitada que possui mais caracteres.'''

x=[]
maior=0

for num in range(10):
	nome = input("Informe uma Palavra: ")
	x.append(nome)
	
	if len(nome) > maior:
		maior = len(nome)
		
for cont in range(10):
	if len(x[cont]) == maior:
		print(x[cont])

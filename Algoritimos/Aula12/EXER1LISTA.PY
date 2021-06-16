'''Faça um programa que possua uma função que recebe uma string e um caractere, e retorne o
número de vezes que esse caractere aparece na string. Por exemplo, se a função receber “teste de
mesa” e o caractere “s”, ela deve retornar 2.'''

#FUNÇÃO

def comparar(c,caracter):
	num = 0
	for i in range(len(caracter)):
		if caracter[i] == c:
			num+=1
	
	print("A letra: {}, aparece: {} vez'es na palavra: {}".format(c,num,caracter))
	
#CODIGO PRINCIPAL	

c = input("Infome uma letra: ")
caracter = input("Informe uma palavra: ")
print()

comparar(c,caracter)

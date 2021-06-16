'''Faça um programa que possua uma função que recebe uma string, sendo que ela deve retornar
uma nova string contendo apenas os caracteres repetidos (que existem mais de uma vez na string
recebida por parâmetro). Por exemplo, se a função receber “teste de mesa”, elas deve retornar “tes”.'''

#FUNÇÃO

def comparar(caracter):
	saida = ""
	for i in caracter:
			if caracter.count(i) >= 2 and saida.count(i) < 1:
				saida += i
				
	print(saida)
	
#CODIGO PRINCIPAL	

caracter = input("Informe uma palavra: ")
print()

comparar(caracter)

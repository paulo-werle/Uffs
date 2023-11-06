'''Implemente um programa que possua uma função que recebe como parâmetro um número
inteiro, e a partir dele imprime a sua tabuada. Se o número recebido for 2, esta função deve
imprimir:
Tabuada do 2:
2 x 1 = 2
2 x 2 = 4
2 x 3 = 6
2 x 4 = 8
2 x 5 = 10
2 x 6 = 12
2 x 7 = 14
2 x 8 = 16
2 x 9 = 18
2 x 10 = 20

Na código principal do programa, faça a chamada desta função para exibir as tabuadas do 2 ao 12.'''

#FUNÇÃO

def taboada(num):
	
	for i in range(1,11):
		print("{}x{}={}".format(num,i,num*i))
		
#CODIGO PRINCIPAL
for i in range(2,13):
	taboada(i)
	print()

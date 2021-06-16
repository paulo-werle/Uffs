'''Faça um programa para calcular o resultado da expressão (x² + 3xy + y) / (2xy + 3x
+ 4y +2) para os valores x = 2, 4, 6, 8 e y = 1, 3, 5, 7. O resultado da expressão deve ser
calculado em uma função, sendo retornado por ela. Como saída, devem ser impressos os valores
calculados para todos os valores de x e y.'''

#FUNÇÃO

def calculo(x,y):
	resultado = (x*x + 3*x*y + y) / (2*x*y + 3*x+ 4*y +2)
	
	return resultado
	
#CODIGO PRINCIPAL
for x in 2,4,6,8:
	for y in 1,3,5,7:
		print("O Resultado da Expressão para {},{} é: {:.2f}".format(x,y,calculo(x,y)))
	print()

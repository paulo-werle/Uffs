'''A sequência de Fibonacci é composta por números inteiros. Os dois primeiros números da
sequência são 0 e 1. O próximo número é calculado como a soma dos dois anteriores, sendo assim,
a sequência completa é: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, .... Faça um programa que
imprima a sequência de Fibonacci, porém o usuário pode escolher quantos números ele deseja
visualizar.
Ex:
Se o usuário informar 5, a saída será: 0, 1, 1, 2, 3.
Se o usuário informar 9, a saída será: 0, 1, 1, 2, 3, 5, 8, 13, 21.'''

cont = int(input("Informe a quantidade de Numeros que gostaria de Ver, sendo aplicada a sequência de Fibonacci"))
num = 1
numero = 0

while cont > 0:
	
	resultado = numero + num
	num = numero
	print (numero, end=", ")
	numero = resultado
	
	cont = cont - 1

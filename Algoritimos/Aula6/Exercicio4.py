'''Faça um programa que receba um número inteiro. O programa mostra a tabuada desse número.
Utilize um laço FOR. Ex: se o usuário informar 4, o programa mostra o seguinte (exatamente dessa
forma):
4 x 1 = 4
4 x 2 = 8
4 x 3 = 12
4 x 4 = 16
4 x 5 = 20
4 x 6 = 24
4 x 7 = 28
4 x 8 = 32
4 x 9 = 36
4 x 10 = 40'''

numero = int(input("Digite um numero "))

for num in range(1,11):
	resultado = numero * num
	print("{} x {} = {}".format(numero,num,resultado))

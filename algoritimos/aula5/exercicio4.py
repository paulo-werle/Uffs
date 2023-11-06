'''Faça um programa que calcule e imprime a soma dos inteiros de 1 a 10. Utilize um laço com as
instruções de cálculo e incremento. O laço deve terminar quando o valor inteiro se tornar 11.'''
num = 0
resultado = 0
cont = 1

while cont <= 10:
	num+= 1
	resultado = resultado + num
	cont += 1
	
print(resultado)


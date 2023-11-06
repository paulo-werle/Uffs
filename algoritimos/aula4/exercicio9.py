'''Faça um programa que receba quatro números e mostre na tela a soma dos números pares e a
soma dos números ímpares informados. Ex: se o usuário informar 2, 3, 6 e 9, o programa mostra
como saída: Soma dos pares: 8, Soma dos impares: 12.'''

n1 = int(input("Digite um numero  "))
n2 = int(input("Digite outro numero  "))
n3 = int(input("Digite mais um numero  "))
n4 = int(input("Digite mais um, mas é o ultimo numero, TAHHH  "))
par = 0

if n1%2 ==1:
	impar = n1
else:
	par = n1
	
if n2%2 == 1:
	impar = impar + n2
else:
	par = par + n2

if n3%2 == 1:
	impar = impar + n3
else:
	par = par + n3
	
if n4%2 == 1:
	impar = impar + n4
else:
	par = par + n4
	
print("A Soma dos numeros Impares é: ", impar)
print("A Soma dos numeros Par é: ", par)

'''Faça um programa que receba um número indefinido de valores inteiros positivos. Quando o
usuário digitar um número menor ou igual a 1, o programa para de pedir números e mostra como
saída quantos números primos foram digitados pelo usuário.'''

n = int(input("Infome N "))
cont= 0

while n > 1:
	aux = n - 1
	primo = True
	while aux > 1:
		if n%aux ==0:
			primo = False
				
		aux -= 1	
		
	if primo:
		cont+=1

	n = int(input("Infome N "))	
	
print(cont)	
		

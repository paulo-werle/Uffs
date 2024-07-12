''' Faça um programa que leia dois números e informe se o primeiro número digitado é divisível
pelo segundo.'''

n1 = int(input("Informe o Valor de A  "))
n2 = int(input("Informe o Valor de B  "))

resultado = n1/n2
#print(type(resultado))

if n1 != n2:
	if (n1%2 == 1)and(n1%2 == 1):
		print("Divisao exata Inexistente")
	else:
		print(int(resultado))
		
elif n1 == n2:
	print(int(resultado))


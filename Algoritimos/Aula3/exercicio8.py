'''Faça um algoritmo que leia os valores A, B e C. Mostre uma mensagem que informe se a soma
de A com B é menor, maior ou igual a C.'''

a = int(input("Informe o Valor de A  "))
b = int(input("Informe o Valor de B  "))
c = int(input("Informe o Valor de C  "))

a = a + b

if a > c:
	print("o Resultado de A e B é MAIOR do que o de C")
	
elif a < c:
	print("o Resultado de A e B é MENOR do que o de C")
	
else:
	print("o Resultado de A e B é IGUAL do que o de C")

'''Sem utilizar a operação de multiplicação, escreva um programa que leia dois números inteiros e
multiplique-os. Por exemplo: 2 * 4 = 2 + 2 + 2 + 2. Utilize um laço FOR.'''

n1 = int(input("Informe o primeiro numero: "))
n2 = int(input("Informe o segundo numero: "))

resultado = 0

for num in range(n2):
	resultado += n1
	if num == (n2-1):
		print(n1, end=" ")
	else:
		print(n1, end=" + ")
print("=" ,resultado)


'''Faça um programa que leia um número N, e calcule a soma
de todos os seus antecessores até 1 utilizando uma função
recursiva. Ex.: se for informado 6, o programa deve somar
6+5+4+3+2+1 e imprimir o resultado.'''

#FUNÇÃO
def antecessor(resultado,n):
	if n == 0:
		return resultado
		
	resultado += n
	return antecessor(resultado,n-1)

#CODIGO PRINCIPAL

n = int(input("Informe o valor para calcular N: "))
resultado = 0
resultado = antecessor(resultado,n)

print(resultado)

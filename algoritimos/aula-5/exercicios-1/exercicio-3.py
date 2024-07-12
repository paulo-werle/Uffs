# Descrição:
'''Faça um programa que leia dois números inteiros positivos (N1 e N2) e imprima o quociente
(Quoc) e o resto (Resto) da divisão de N1 por N2, utilizando apenas as operações de adição e
subtração.
Ex.: N1=10; N2=2 => Quoc=5 Resto=0'''

n1 = int(input("Informe o primeiro valor "))
n2 = int(input("Informe o segundo valor "))
quoc = 0

while n1 >= n2:
	n1 = n1-n2
	quoc += 1

print("Quoc={} Resto={}".format(quoc,n1))


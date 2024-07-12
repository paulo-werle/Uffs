# Descrição:
'''Faça um programa que receba um número inteiro e informe se esse número é primo ou não. Um
número primo é aquele que só é divisível por 1 e por ele mesmo. Ex: 2, 5, 13 e 17.'''

n = int(input("Infome N "))
aux = n - 1
primo = True
while aux > 1:
	if n%aux ==0:
		primo = False

	aux -= 1

if primo:
		print("O numero {} é Primo".format(n))
else:
		print("O numero {} não é Primo".format(n))

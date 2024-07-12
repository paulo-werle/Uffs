# Descrição:
'''Faça um programa que determine e mostre os cinco primeiros múltiplos de 3, considerando
números maiores que 0.'''
p = 1
num = 1

while p <= 5:

	if num %3 == 0:
		print (num)
		p += 1

	num += 1


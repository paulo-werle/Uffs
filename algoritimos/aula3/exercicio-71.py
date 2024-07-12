'''Faça um programa que receba três números inteiros e informe qual deles é o maior e qual deles é
o menor.'''

n1 = int(input("Informe o Primeiro Numero  "))

maior = n1
menor = n1

n2 = int(input("Informe o Segundo Numero  "))

if n2 > maior:
	maior = n2

if n2 < menor:
	menor = n2
	
n3 = int(input("Informe o Terceiro Numero  "))

if n3 > maior:
	maior = n3

if n3 < menor:
	menor = n3
	
print("O Maior numero é: ", maior)
print("O Menor numero é: ", menor)

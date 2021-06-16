'''Crie um programa que peça o nome, a altura e o peso de quatro pessoas e apresente o nome e
peso da mais pesada e o nome e altura da mais alta. Obs. utilizar repetição com FOR.'''
import os

nome = input("Informe seu nome: ")
peso = float(input("Informe seu peso: "))
altura = float(input("Informe seu peso: "))

maisalta = altura
nomealta = nome
maispeso = peso
nomepeso = nome

for num in range(4):
	os.system("cls")
	
	nome = input("Informe seu nome: ")
	peso = float(input("Informe seu peso: "))
	altura = float(input("Informe seu peso: "))

	if altura > maisalta:
		maisalta = altura
		nomealta = nome
		
	if peso > maispeso:
		maispeso = peso
		nomepeso = nome
		
print("O nome da pessoa mais alta é :{}, e ela mede é :{:.2f} Metros".format(nomealta,maisalta))
print("O nome da pessoa mais pesada é :{}, e ela pesa é :{:.2f} KG".format(nomepeso,maispeso))

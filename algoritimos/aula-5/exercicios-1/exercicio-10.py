# Descrição:
'''Crie um programa que peça o nome, a altura e o peso de quatro pessoas e apresente o nome e
peso da mais pesada e o nome e altura da mais alta. Obs. utilizar repetição com while.'''
import os

cont = 1

nome = input("Informe o Nome ")
peso = float(input("Informe o Peso do Individuo "))
altura = float(input("Informe a Altura do Individuo "))

maisalta = altura
maispeso = peso
nomealta = nome
nomepeso = nome

os.system("cls")

while cont < 4:

	nome = input("Informe o Nome ")
	peso = float(input("Informe o Peso do Individuo "))
	altura = float(input("Informe a Altura do Individuo "))

	if altura > maisalta:
		maisalta = altura
		nomealta = nome

	elif peso > maispeso:
		maispeso = peso
		nomepeso = nome

	os.system("cls")

	cont += 1

print("A Pessoa com maior altura é {}, medindo exatamente: {:.2f} MT".format(nomealta,maisalta))
print("A Pessoa com maior peso é {}, pesando exatamente: {:.2f} KG".format(nomepeso,maispeso))


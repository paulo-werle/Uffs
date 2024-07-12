'''Faça um programa que leia 5 jogos de videogame, sendo que eles possuem as informações de
nome, estilo, fabricante e preço em dólares (US$). Depois, imprima estes 5 jogos, mostrando os
seus dados e também o seu preço em reais (R$). Considere a taxa de câmbio: US$ 1,00 = R$ 3,98.'''

#ESTRUTURAS

class Jogo:
	nome=""
	estilo=""
	fabricante=""
	preco=0.0
	
#FUNÇÃO

def Jogos():
	Jogos=[]
	for i in range(5):
		j = Jogo()
		j.nome = input("Informe o Nome do Jogo: ")
		j.estilo = input("Informe o Estilo do Jogo: ")
		j.fabricante = input("Informe o Nome do Fabricante: ")
		j.preco = float(input("Informe o Preço do Jogo em US$: "))
		print()
		Jogos.append(j)
	
	return Jogos
	
def Reais(Jogos):
	preco=[]
	for i in range(5):
		valor = Jogos[i].preco*3.98
		preco.append(valor)
		
	return preco
	
def Imprimir(Jogos,preco):
	for i in range(5):
		print('''O nome do Jogo é: {}
		O estilo: {}
		O fabricante: {}
		O preço em US$: {}
		O Preço em Reais: {} '''.format(Jogos[i].nome,Jogos[i].estilo,Jogos[i].fabricante,Jogos[i].preco,Preco[i]))
	
#CODIGO PRINCIPAL

Jogos = Jogos()
preco = Reais(Jogos)
Imprimir(Jogos,preco)




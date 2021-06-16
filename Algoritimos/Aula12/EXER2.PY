'''Faça um programa que leia os dados de 5 bandas de música (estrutura composta pelo nome da
banda, estilo musical e número de integrantes), armazenando-as em uma lista. Depois, leia um
número de 1 a 5, que corresponde a uma das bandas previamente lidas. A partir deste número,
imprima os dados da banda solicitada.'''

#ESTRUTURAS

class banda:
	nome=""
	estilo=""
	integrantes=0
	
#FUNÇÃO
def ler_bandas():
	bandinha=[]
	for i in range(5):
		b = banda()
		b.nome = input("Informe o Nome da Banda: ")
		b.estilo = input("Informe o Estilo de Musica da Banda: ")
		b.integrantes = int(input("Informe quantos integrantes a banda possui: "))
		print()
		bandinha.append(b)
	
	return bandinha
	
#CODIGO PRINCIPAL

n = int(input("Informe um numero: "))

bandinha = ler_bandas()

n = n-1
print("O Nome da Banda é {}".format(bandinha[n].nome))
print("O Estilo das musicas é {}".format(bandinha[n].estilo))
print("Possui {} integrantes".format(bandinha[n].integrantes))


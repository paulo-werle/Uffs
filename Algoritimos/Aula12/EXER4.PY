'''Faça um programa que leia os dados de 5 estádios de futebol e armazene-os em uma lista, sendo
sua estrutura representada pela estrutura abaixo:
class Estadio:
nome = ""
capacidadePublico = 0
recordPublico = 0
Após ler os dados dos estádios, faça duas funções:
maior_capacidade(lista): percorre a lista de estádios, retornando o estádio com maior capacidade.
maior_publico(lista): percorre a lista de estádios, retornando o estádio com maior record de
publico;
Ao final, imprima o nome do estádio com maior capacidade e com maior record de público que
foram retornados pelas funções.'''

#ESTRUTURAS

class Estadio:
	nome = ""
	capacidadePublico = 0
	recordPublico = 0

#FUNÇÃO

def maior_capacidade(Estadios):
	capacidade = 0
	for i in range(5):
		if Estadios[i].capacidadePublico > capacidade:
			capacidade = Estadios[i].capacidadePublico
			maiorPub = Estadios[i]
			
	return maiorPub
			
def maior_publico():
	publico = 0
	for i in range(5):
		if Estadios[i].recordPublico > publico:
			publico = Estadios[i].recordPublico
			maiorRec = Estadios[i]
			
	return maiorRec

#CODIGO PRINCIPAL

Estadios = []
for i in range(5):
	e = Estadio()
	e.nome = input("Informe o Nome do Estadio: ")
	e.capacidadePublico = int(input("Informe a Capacidade de Publico no Estadio: "))
	e.recordPublico = int(input("Informe o Record de Publico no Estadio: "))
	print()
	Estadios.append(e)
	
maiorPub = maior_capacidade(Estadios)
maiorRec = maior_publico()

print('''O Estadio com Maior capacidade é o {}
,que suporta: {} pessoas e seu Record de publico é {}'''.format(maiorPub.nome,maiorPub.capacidadePublico,maiorPub.recordPublico))
print()
print('''O Estadio com Maior Record é o {}
,que suporta: {} pessoas e seu Record de publico é {}'''.format(maiorRec.nome,maiorRec.capacidadePublico,maiorRec.recordPublico))

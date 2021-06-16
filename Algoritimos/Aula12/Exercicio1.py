'''Baseado nos exemplos 1 e 2, faça um
programa que após ler 5 pessoas, encontre e
imprima a mais velha.'''

class Pessoa: #Estrutura Pessoa
	nome = ""
	idade = 0
	peso = 0
	altura = 0.0
	
def ler_pessoa(numeroPessoa): #Função que lê os dados da pessoa e a retorna
	print("\nPessoa", numeroPessoa)
	pes = Pessoa()
	pes.nome = input("Informe o nome: ")
	pes.idade = int(input("Informe a idade: "))
	pes.peso = int(input("Informe o peso: "))
	pes.altura = foat(input("Informe a altura: "))
	
	return pes #retorna a variável do tipo Pessoa
		
	
#Código principal...
pessoas = []

for i in range(5):
	pessoas.append( ler_pessoa(i+1) ) #Adiciona a pessoa na lista
	
if

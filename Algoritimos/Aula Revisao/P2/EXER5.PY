'''Faça um programa que possua uma estrutura para representar um computador (processador,
quantidade de memória RAM e tamanho do HD), sendo que devem ser lidos 3 computadores e
armazenados em um vetor. Após isso, faça a impressão dos seus dados. O programa deve utilizar as
funções, conforme as assinaturas abaixo:
ler_computador() - lê as informações de um computador, retornando-o;
imprimir_computador(comp) - imprime os dados do computador recebido por parâmetro;'''

#ESTRUTURAS

class computador:
	processador = ""
	qnt_m_ram = 0
	hd = 0
	
#FUNÇÕES

def ler_computador(i):
	c = computador()
	c.processador = input("Informe qual é o processador do {}º computador: ".format(i+1))
	c.qnt_m_ram = input("Informe qual é a quantidade de memoria RAM do {}º computador: ".format(i+1))
	c.hd = input("Informe qual é a quantidade de memoria do HD do {}º computador: ".format(i+1))
	print()
	
	return c
	
def imprimir_computador(comp):
	for i in range(3):
		print("o Processador do computador é: ",comp[i].processador)
		print("A quantidade de memoria RAM é: ",comp[i].qnt_m_ram)
		print("A quantidade de memoria em HD é: ",comp[i].hd)
		print()


#CODIGO PRINCIPAL
comp = []

for i in range(3):
	c = ler_computador(i)
	comp.append(c)
	
imprimir_computador(comp)

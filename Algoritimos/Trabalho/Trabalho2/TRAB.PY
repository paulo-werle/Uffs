'''Escrever um programa em linguagem Python que controle as retiradas de dinheiro de um cofre. O
fluxo do programa é o seguinte:'''
#1- Ao iniciar, ele solicita ao usuário o valor total de dinheiro que pode ser retirado do cofre naquela
#execução do programa;
#2- Em seguida, o programa fica recebendo valores inteiros, que correspondem a retiradas de
#dinheiro do cofre. Cada vez que um número é informado, o programa mostra a saída das notas
#utilizadas e o quanto de dinheiro ainda pode ser retirado; depois, o programa volta a receber valores
#para uma nova retirada.
#3- Quando uma retirada com valor menor ou igual a R$ 0 for informado, o programa termina.
#Quando uma retirada é feita, o programa sempre deve fornecer o menor número possível de notas.
#Considere que podem ser fornecidas notas de R$ 100, R$ 50, R$ 20, R$ 10 e R$ 5. Por exemplo, se
#a retirada do cofre for de R$ 50, o programa deve informar que uma nota de R$ 50 foi usada, não 5
#notas de R$ 10.
'''O resultado de uma retirada tem o seguinte formato (usando o exemplo de uma retirada de R$ 50 e
que o valor total seja R$ 570):
Notas sacadas:
R$ 100 – 0
R$ 50 – 1
R$ 20 – 0
R$ 10 – 0
R$ 05 – 0
Valor restante no cofre: R$ 520
Se for realizada uma nova retirada de R$ 275, o resultado deve ser:
Notas sacadas:
R$ 100 – 2
R$ 50 – 1
R$ 20 – 1
R$ 10 – 0
R$ 05 – 1
Valor restante no cofre: R$ 245'''
'''Cada vez que uma retirada é feita, seu valor deve (obviamente) ser descontado do valor total de
dinheiro que pode ser retirado do cofre naquela execução do programa (lido no passo 1),
atualizando assim o valor restante no cofre. Caso o valor da retirada for maior que o valor restante
no cofre, o programa deve exibir a mensagem "Não é possível sacar este valor!". Caso não exista
uma combinação de notas possíveis para o valor da retirada, também deve ser mostrada a
mensagem "Não é possível sacar este valor!". Exemplo:
Retirada de R$ 52:'''
#Não é possível sacar este valor!

# AUTOR: PAULO EDUARDO RODRIGUES WERLE
# EMAIL: pauloeduardo840@gmail.com

dinheiro = float(input("Informe a quantidade de Dinheiro que pode ser retirado do Cofre: R$"))

retirada = int(input("Quanto voce deseja retirar?? R$"))

while retirada > 0:
	
	if dinheiro >= retirada:
		
		saida = retirada

		cem = 0
		cinquenta = 0
		vinte = 0
		dez = 0
		cinco = 0

		while saida >= 100:
			saida-= 100
			cem += 1
							
		while saida >= 50 and saida < 100:
			saida -= 50
			cinquenta += 1
							
		while saida >= 20 and saida < 50:
			saida -= 20
			vinte += 1
							
		while saida >= 10 and saida < 20:
			saida -= 10
			dez += 1
							
		while saida >= 5 and saida < 10:
			saida -= 5
			cinco += 1
							
		while saida < 5 and saida != 0:
			print("\n Não é possível sacar este valor !  \n")
			saida = 0
			retirada = 0
			cem = 0
			cinquenta = 0
			vinte = 0
			dez = 0
			cinco = 0
			
		dinheiro = dinheiro - retirada	
			
		print('''Notas sacadas:
				R$ 100 – {}
				R$ 50  – {}
				R$ 20  – {}
				R$ 10  – {}
				R$ 05  – {}
				Valor restante no cofre: R$ {:.2f}'''.format(cem,cinquenta,vinte,dez,cinco,dinheiro))
		
	else:
		print("Não é possível sacar este valor!")
		
	retirada = int(input("Quanto voce deseja retirar?? R$"))

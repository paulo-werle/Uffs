#DESCRIÇÃO DO PROGRAMA

'''Escrever um programa em linguagem Python que ajude um comerciante a calcular o preço final de
um produto baseado na opção de pagamento do cliente. O programa deve receber como entradas o
valor do produto (float) e a quantidade de parcelas que o cliente escolheu pagar (int). Considere que
o usuário sempre digitará valores positivos para as entradas.
O preço final do produto varia conforme a quantidade de parcelas que o cliente escolheu. A tabela
abaixo mostra as alterações no preço do produto com base no número de parcelas:'''
#Pagamento avista
'''Se o produto custar menos de R$ 300, o preço
não se altera. Se o produto custar entre R$ 300 e
R$ 500, o preço recebe um desconto de 10%. Se
o produto custar mais de R$ 500, o preço recebe
um desconto de 25%.'''
#Duas Parcelas
'''Nenhuma alteração.'''
#Tres Parcelas
'''Se o produto custar até R$ 1100, há um aumento
de 10% no preço. Se o produto custar mais de
R$ 1100, há um aumento de 20% no preço.'''
#Quatro Parcelas
'''Nenhuma alteração.'''
#Cinco ou mais Parcelas
'''O preço recebe um aumento de 25%.'''
'''Como saída, o programa mostra seguinte mensagem, contendo o preço final do produto e o valor de
cada parcela que o cliente terá de pagar:
O preço final é R$ XXX.XX, parcelado em X vez(es) de R$ XXX.XX.
O programa deve ser executado com o Python 3.'''

# Autor: PAulo Werle
# Email: pauloeduardo840@gmail.com


valor = float(input("Informe o valor do produto  R$"))
qnt = int(input("Informe em quantas parcelas o cliente gostaria de pagar  "))


if qnt == 1:
	
	if valor < 300.00:
		parcela = valor
		
	elif valor >= 300.00 and valor <= 500.00:
		parcela = valor * 0.90
		
	elif valor > 500.00:
		parcela = valor * 0.75
		
elif qnt == 2:
	parcela = valor / qnt
	
elif qnt == 3:

	if valor <= 1100.00:
		parcela = (valor * 1.10)/ qnt
		
	elif valor > 1100.00:
		parcela = (valor * 1.20)/ qnt
		
elif qnt == 4:
	parcela = valor / qnt
	
elif qnt >= 5:
	parcela = (valor * 1.25) / qnt
	
print("O preço final é R$ {:.2f}, parcelado em {} vez(es) de R$ {:.2f}.".format(valor,qnt,parcela))

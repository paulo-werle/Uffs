'''Escreva um programa que, para uma conta bancária, leia o seu número e o saldo atual. Após isso,
deve-se ler operações (valor e tipo da operação). O tipo de operação a ser realizada é identificado
pela sua primeira letra: D=depósito ou R=retirada. Após cada operação, determine e mostre o novo
saldo. Se a operação for diferente de D ou R, deve ser mostrada a mensagem “Operação inválida”,
sendo lido novamente o tipo da operação. O programa deve finalizar quando o valor da operação for
0. Após isso, deve-se mostrar o número da conta e o saldo final. Se esse saldo for negativo, deve ser
mostrada, também, a mensagem “Conta estourada!”.'''

conta = int(input("Informe a Conta Bancaria: "))
saldoat = float(input("Informe o Saldo Atual: "))
saldoop = float(input("Informe o Valor da Operação: "))

while saldoop != 0:

	operação = input("Informe a Operação Desejada: ")

	if operação in "Dd":
		saldoat = saldoat + saldoop
	
	elif operação in "Rr":
		saldoat = saldoat - saldoop
		
	else:
		print("Operação inválida")
		
	if saldoat < 0:
		print("Conta estourada!")
		
	else:
		print ("Numero da Conta: {0}, Saldo Atual:{1:.2f}".format(conta,saldoat))
	
	saldoop = float(input("Informe o Valor da Operação: "))

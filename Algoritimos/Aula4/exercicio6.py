'''Escreva um programa que, para uma conta bancária, leia o seu número, o saldo atual, o tipo de
operação a ser realizada (depósito (D) ou retirada (R)) e o valor da operação. Após, determine e
mostre o novo saldo. Se o novo saldo ficar negativo, deve ser mostrada, também, a mensagem
“conta estourada”. Se a operação for diferente de D ou R, deve ser mostrada a mensagem
“Operação inválida”.'''

numero = int(input("Conta Bancaria  "))
saldo = float(input("Saldo Atual  "))
op = input("Informe a Operação a ser Realizada com ( D ) para Deposito e ( R ) para Retirada  ")
valor = float(input("Valor da Operação  "))


if op in "Dd":
	saldo = saldo + valor
	
elif op in "Rr":
	saldo = saldo - valor
	
else:
	print("Operação inválida")

if saldo < 0:
	print("CONTA ESTOURADA")
	
else:
	print("O saldo Atual é R$ {0:.2f}".format(saldo))

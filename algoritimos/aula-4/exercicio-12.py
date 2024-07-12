# Descrição:
'''Sabendo que a tabela de imposto de renda aplica uma alíquota para as seguintes faixas de
valores:
• Até 1.903,98 = Isento
• De 1.903,99 até 2.826,65 = 7,5%
• De 2.826,66 até 3.751,05 = 15,0%
• De 3.751,06 até 4.664,68 = 22,5%
• Acima de 4.664,68 = 27,5%
Faça um programa que leia o valor de um salário bruto e, de acordo com as faixas acima, calcule o
valor do imposto e o valor do salário líquido. Calcule também o valor da alíquota efetiva, isto é, o
valor de imposto pago em relação ao salário bruto.
Exemplo:
Salário bruto: R$ 3.500,00
Até 1.903,98 = isento;
De 1.903,99 até 2.826,65 = R$ 69,20;
De 2.826,66 até 3.500,00 = R$ 101,00;
Valor de imposto = R$ 170,20 Salário líquido: 3.329,80 Alíquita efetiva: 4,86%'''

salario = float(input("Informe o Salario: R$ "))

imposto = 0
salario1 = salario

salariofaixa = salario1 - 4.664,68

if salariofaixa > 0:
	imposto = imposto * (salariofaixa*0,275)
	salario1 = salario1 - salariofaixa

salariofaixa = salario1 - 3.751,06

elif salariofaixa > 0:
	imposto = imposto * (salariofaixa*0,225)
	salario1 = salario1 - salariofaixa

salariofaixa = salario1 - 2.826,66

elif salariofaixa > 0:
	imposto = imposto * (salariofaixa*0,15)
	salario1 = salario1 - salariofaixa

salariofaixa = salario1 - 1.903,99

elif salariofaixa > 0:
	imposto = imposto * (salariofaixa*0,075)
	salario1 = salario1 - salariofaixa

print("VAlor de imposto = R$ {:2f},  Salario Liquido = R$ {:.2f},  Aliquota efetiva {:.2f}".format(imposto,salario,imposto(imposto/salario))

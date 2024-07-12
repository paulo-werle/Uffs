# Descrição:
'''Uma empresa produz três tipos de peças mecânicas: parafusos, porcas e arruelas. Têm-se os
preços unitários de cada tipo de peça (R$ 0,10, R$ 0,08, R$ 0,03, respectivamente) e sabe-se que
sobre estes preços incidem descontos de 10% para porcas, 20% para parafusos e 30% para arruelas.
Escreva um programa que calcule o valor total da compra de um cliente. O nome do cliente e o
número de cada peça vendida deve ser informado pelo usuário. Ao final, o programa deve mostrar o
nome do cliente, o valor pago por cada tipo de peça (sem desconto), o total de desconto e o total a
pagar pela compra.'''

import os

nome = input("Nome do Cliente: ")
p1 = int(input("Informe quantos parafusos o Cliente quer comprar: "))
p2 = int(input("Informe quantos porcas o Cliente quer comprar: "))
p3 = int(input("Informe quantos arruelas o Cliente quer comprar: "))
desconto = 0

os.system("cls")

if p1>0:
	desconto = desconto + (p1*0.02)

if p2>0:
	desconto = desconto + (p2*0.0008)

if p3>0:
	desconto = desconto + (p3*0.0009)

else:
	print("Produto Inexistente")

p1 = p1 * 0.10
p2 = p2 * 0.08
p3 = p3 * 0.03
valor = (p1 + p2 + p3) - desconto

print("Nome do Cliente: ", nome)
print("O valor pago pelos parafusos é de: R$", p1)
print("O valor pago pelos porcas é de: R$", p2)
print("O valor pago pelos arruelas é de: R$", p3)
print("O total de Descontos pela compra é de: R$", desconto)
print("O Valor Total da compra é de: R$", valor)

# Descrição:
'''Um usuário deseja um programa pelo qual possa escolher que tipo de média deseja calcular a
partir de três notas. Faça um programa que leia as notas, a opção escolhida pelo usuário e calcule a
média. As opções são:
1- aritmética
2- ponderada (pesos 3, 3, 4)
Caso a opção seja diferente de 1 ou 2, deve ser mostrada a mensagem “Opção inválida”.'''

n1 = float(input("Informe a Primeira Nota:  "))
n2 = float(input("Informe a Segunda Nota:  "))
n3 = float(input("Informe a Terceira Nota:  "))

t = int(input("Digite 1 para calcular a MEDIA ARITMEDICA das notas e 2 para calcular a MEDIA PONDERADA:  "))

if t == 1:
	media = (n1 + n2 + n3)/3
	print("A Media Obtida é: ", media)

elif t == 2:
	media = (n1*3 + n2*3 + n3*4)/ (3 + 3 + 4)
	print("A Media Obtida é: ", media)

else:
	print("Opção inválida")

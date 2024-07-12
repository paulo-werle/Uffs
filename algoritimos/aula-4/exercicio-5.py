# Descrição:
'''Uma empresa irá dar um aumento de salário aos seus funcionários de acordo com a categoria de
cada empregado. O aumento seguirá a seguinte regra:
• Funcionários das categorias A, C, F, e H ganharão 10% de aumento sobre o salário;
• Funcionários das categorias B, D, E, I, J e T ganharão 15% de aumento sobre o salário;
• Funcionários das categorias K e R ganharão 25% de aumento sobre o salário;
• Funcionários das categorias L, M, N, O, P, Q e S ganharão 35% de aumento sobre o salário;
• Funcionários das categorias U, V, X, Y, W e Z ganharão 50% de aumento sobre o salário.
Faça um programa que leia o nome, a categoria e salário de um funcionário, e imprima o nome,
categoria e salário reajustado do mesmo.'''


nome = input("Informe o Nome:  ")
categoria = input ("Informe a Categoria em que atua:  ")
salario = float(input("Informe o Salario:  "))


if categoria in "ACFH" or categoria in "acfh":
	salario = (salario * 1.1)

elif categoria in "BDEIJT" or categoria in "bdeijt":
	salario = (salario * 1.15)

elif categoria in "KR" or categoria in "kr":
	salario = (salario * 1.25)

elif categoria in "LMNOPQS" or categoria in "lmnopqs":
	salario = (salario * 1.35)

elif categoria in "UVXYWZ" or categoria in "uvxywz":
	salario = (salario * 1.50)

else:
	categoria = "Inexistente"

print("O Nome do Funcionario é:  ", nome)
print("A Categoria do Funcionario é:  ", categoria)
print("O Salario Reajustado do Funcionario é:  ", salario)



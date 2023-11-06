'''Faça um programa que calcule a média de salários de uma empresa, pedindo ao usuário o nome
dos funcionários e os salários. No fim, informe a média, o salário mais alto e o salário mais baixo
(nome e salário). Use nome = “fim” para encerrar a leitura.'''

nome = input("Informe o Nome do Funcionario ")

import os
cont = 0
empresa = 0
salariomenor = 1000000000
salariomaior = - 1000000000

while nome != "fim":
	salario = float(input("Informe o Salario desse Funcionario "))
	
	if salario > salariomaior:
		salariomaior = salario
		nomemaior = nome
	
	if salario < salariomenor:
		salariomenor = salario
		nomemenor = nome
		
	os.system("cls")	
	empresa = empresa + salario
	cont+= 1
	
	nome = input("Informe o Nome do Funcionario ")
	
empresa = empresa/cont

print("A Media de Salarios da Empresa é:{:.2f}".format(empresa))
print("O Maior salario da Empresa é do(a):R${0}, e seu salario é de: R${1:.2f}".format(nomemaior, salariomaior))
print("O Menor salario da Empresa é do(a):R${0}, e seu salario é de: R${1:.2f}".format(nomemenor, salariomenor))

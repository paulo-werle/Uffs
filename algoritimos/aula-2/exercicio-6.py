'''Considere a seguinte situação descontam-se inicialmente 10% do salario bruto do trabalhador como contribuição a previdencia social.
Após esse desconto, ha um outro desconto de 5% sobre o valor restante do salario bruto a titulo de determinado imposto.
Leia o nome e o salario bruto de um trabalhador e calcule seu salario liquido.
A mensagem de saida deve ser " O trabalhador XX possui salario liquido de R$ XXX".'''

nome = input("Informe o Nome do Fucionario  ")
salario = float(input("Informe o salario do funcionario  "))

salario = (salario*0.9)*0.95

print("O trabalhador", nome, " possui salario liquido de R$ ",salario)


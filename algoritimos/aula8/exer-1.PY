'''Escreva um programa que leia um número de 1 a 12 (usando input) e, com base neste número,
imprima o mês correspondente. O programa deve guardar e procurar o mês correspondente ao
número em uma lista.'''

lista = ["Janeiro","Fevereiro","Março","Abril","Maio","Junho","Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"]

i = int(input("Informe um Mes: "))
i-=1

print(lista[i])

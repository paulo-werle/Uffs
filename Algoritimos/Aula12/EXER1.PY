'''Faça um programa que leia 5 datas, sendo que as mesmas devem ser armazenadas na seguinte
estrutura:
class Data:
ano = 0
mes = 0
dia = 0
Após ler das datas, imprima a menor. Exemplo: 20/05/1990 é menor que 01/01/2000.'''

class Data:
	ano = 0
	mes = 0
	dia = 0

Date = []
for i in range(5):	
	d = Data()
	
	d.dia = int(input("Informe o Dia"))
	d.mes = int(input("Informe o Mes"))
	d.ano = int(input("Informe o Ano"))
	print()
	Date.append(d)
	
menor = Date[0]

for j in range(1, 5):
	if Date[j].ano <= menor.ano and Date[j].mes <= menor.mes and Date[j].dia < menor.dia:
		menor = Date[j]
		
print("{}/{}/{}".format(menor.dia,menor.mes,menor.ano))


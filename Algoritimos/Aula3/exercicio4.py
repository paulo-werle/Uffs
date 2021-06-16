'''Elabore um programa que leia a idade de um nadador e informe sua categoria:
Mini: menor de 5 anos
Infantil A: de 5 a 7 anos
Infantil B: de 8 a 10 anos
Juvenil A: de 11 a 13 anos
Juvenil B: de 14 a 17 anos
Adulto: a partir de 18 anos.'''

idade = int(input("Informe a Idade do Nadador  "))

if idade<5:
	print("Categoria: MINI")

elif (idade>=5)and(idade<=7):
	print("Categoria: INFANTIL A")

elif (idade>=8)and(idade<=10):
	print("Categoria: INFANTIL B")
	
elif (idade>=11)and(idade<=13):
	print("Categoria: JUVENIL A")
	
elif (idade>=14)and(idade<=17):
	print("Categoria: JUVENIL B")
	
elif idade>=18:
	print("Categoria: ADULTO")
	
else:
	print("Categoria: INEXISTENTE")
	

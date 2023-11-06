'''Faça um programa que possua uma estrutura
Carro com os atributos: modelo, marca e ano
de fabricação. Após, leia os valores para os 3
carros em uma função, retornando a lista com
os 3 carros para o código principal.'''

#ESTRUTURAS

class carro:
	modelo=""
	marca = ""
	ano = 1

#FUNÇÃO
	
def ler_carros():
	carros=[]
	for i in range(3):
		car = carro()
		car.modelo = input("Informe o Modelo do Veiculo:   ")
		car.marca = input("Informe a Marca do Veiculo:   ")
		car.ano = int(input("Infrome o Ano do Veiculo:   "))
		print()
		carros.append(car)
	
	return carros
	

#CODIGO PRICIPAL

carros = ler_carros()

for car in carros:
	print()
	print("O modelo é: ",car.modelo)
	print("O modelo é: ",car.marca)
	print("O modelo é: ",car.ano)

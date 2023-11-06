numero = int(input("Digite numeros impares e pares, ou digite 0 para sair "))
par = 0
impar = 0

while numero != 0:
	
	if numero%2 == 1:
		impar += 1
	else:
		par += 1
	
	numero = int(input("Digite numeros impares e pares, ou digite 0 para sair "))
	
print("Quantidade dos pares: {}, Quantidade dos impares: {}.".format(par,impar))

'''Escreva um algoritmo que calcule o produto dos inteiros ímpares de 1 a 15 e, então, exiba os
resultados. Utilize um laço FOR.'''

resultado = 1

for num in range(1,16):
	
	if num%2==1:
		resultado *= num
		
print("O Produto dos numeros impares de 1 a 15 é: ",resultado)

'''Faça um algoritmo que imprima todos os números pares compreendidos entre 85 e 907. O
algoritmo deve também calcular a soma destes valores. Utilize um laço FOR.'''

resultado = 0

for num in range(85,908):
	
	if num%2==0:
		resultado += num
		
print("A Soma dos numeros pares de 85 a 907 é: ",resultado)

'''Escreva um programa que calcule os N primeiros números da série numérica de RICCI. Esta
série é iniciada por dois números A e B que devem ser lidos pelo programa, sendo ambos positivos
e B maior que A. Os demais termos da série são calculados a partir da soma dos dois elementos
anteriores. Portanto, o terceiro elemento será o resultado da soma de A + B. Considere que o
número de elementos da série nunca será menor que 3.'''

n = int(input("Informe quantos numeros deseja calucular "))

if n >= 3:
	
	n1 = int(input("Informe o primeiro Numero "))
	n2 = int(input("Informe o segundo Numero "))
	
	for num in  range(n):
		resultado = n1 + n2
		n1 = n2
		n2 = resultado
		
		print(resultado, end=" ")
	print()
	
else:
	print("SO FUNCIONARA SE VC DESEJAR VER MAIS DO QUE DOIS VALORES")


'''Faça um programa para calcular o resultado da função abaixo para x = 2, 4, 6, 8 e y = 1, 3, 5, 7,
9, combinando todos os valores possíveis de x e y:
f(x,y) = (x + 3xy + y) / (2xy + 3x + 4y +2)
Como saída, devem ser impressos os valores de x, de y e de f(x,y). Utilize somente laços FOR.'''


for y in range(1,10,2):
	
	for x in range(2,9,2):
		resposta = (x + (3*x*y) + y)/((2*x*y) + (3*x) + (4*y) +2)
		print("A Resposta da Função :f({},{}) = (x + 3xy + y) / (2xy + 3x + 4y +2) é {:.2f}".format(x,y,resposta))
		
	print()

'''1. Implemente um programa que exiba a tabuada do 2 ao 9:
a) Utilizando o laço FOR.
b) Utilizando o laço WHILE.
Exemplo de saída:
Tabuada do 2:
2 x 1 = 2
2 x 2 = 4
2 x 3 = 6
2 x 4 = 8
2 x 5 = 10
2 x 6 = 12
2 x 7 = 14
2 x 8 = 16
2 x 9 = 18
2 x 10 = 20
Tabuada do 3:
3 x 1 = 3
3 x 2 = 6
3 x 3 = 9
3 x 4 = 12
3 x 5 = 15
3 x 6 = 18
3 x 7 = 21
3 x 8 = 24
3 x 9 = 27
3 x 10 = 30
Tabuada do 4:
...'''
for i in range(2,10):
	for j in range(1,11):
		resposta = i * j
		print("{}x{}={}".format(i,j,resposta))
	print()

'''Faça um programa, utilizando laços aninhados, que imprima a seguinte saída:
00 01 02 03 04 05
10 11 12 13 14 15
20 21 22 23 24 25
30 31 32 33 34 35
40 41 42 43 44 45
50 51 52 53 54 55'''

for i in range(6):
	for j in range(6):
		print(end=" {}{}".format(i,j))
	print()

'''Dada a seguinte matriz 5 x 5:
1   8   3   22  30
21  12  9   16  31
14  7   5   8   19
10  25  24  4   9
5   18  16  26  20
Faça um programa que percorra a matriz e substitua os números ímpares por 0.'''

matriz=[[1,8,3,22,30],[21,12,9,16,31],[14,7,5,8,19],[10,25,24,4,9],[5,18,16,26,20]]

for i in range(5):
	for j in range(5):
		if matriz[i][j]%2==1:
			matriz[i][j] = 0
			
		if matriz[i][j]%2==0:
			print(matriz[i][j],end="  ")
	print()

'''Faça um programa, utilizando laços aninhados, que imprima a seguinte saída:
* * * * * * * * * *
* *               *
*   *             *
*     *           *
*       *         *
*         *       *
*           *     *
*             *   *
*               * *
* * * * * * * * * *'''

for i in range(1,11):
	
	for j in range(1,11):
		
		if j == 1 or j == 10:
			print(end=" *")
		
		elif i == 1 or i == 10:
			print(end=" *")
		
		elif j > i or j < i:
			print(end="  ")
	
		elif j == i:
			print(end=" *")
			
	print()

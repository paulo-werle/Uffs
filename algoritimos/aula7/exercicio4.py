'''Faça um programa, utilizando laços aninhados, que imprima a seguinte saída:
 *
   *
     *
       *
         *
           *
             *
               *
                 *
                   *'''
                   
for i in range(1,10):
	
	for j in range(1,10):
		
		if j > i or j < i:
			print(end="  ")
	
		if j == i:
			print(end=" *")
			
	print()

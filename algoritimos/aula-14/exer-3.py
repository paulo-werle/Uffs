import turtle

#Cria a caneta
des=turtle.Turtle()

espaço = 10
tamanho = 5

for i in range(10):
	des.penup()
	des.forward(espaço)
	des.pendown()

	for j in range(3):
		des.forward(tamanho)
		des.right(120)
	
	espaço+= 3
	tamanho += 3
		
		
turtle.done()	
		

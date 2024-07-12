import turtle

#Cria a caneta
des=turtle.Turtle()

cont = 200
for num in range(10):
	cont-=15
	#Vai para dentro
	des.right(45)
	des.penup()
	des.forward(10)
	des.left(45)
	des.pendown()

	#Quadrado de Dentro
	for j in range(4):
		des.forward(cont)
		des.right(90)

turtle.done()

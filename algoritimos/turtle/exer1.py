import turtle

#Cria a caneta
des=turtle.Turtle()

#Quadrado de Fora
des.forward(100)
des.right(90)
des.forward(100)
des.right(90)
des.forward(100)
des.right(90)
des.forward(100)
des.right(90)

# Vai para dentro
des.right(45)
des.penup()
des.forward(10)
des.left(45)
des.pendown()

#Quadrado de Dentro
des.forward(85)
des.right(90)
des.forward(85)
des.right(90)
des.forward(85)
des.right(90)
des.forward(85)
des.right(90)
 

turtle.done()

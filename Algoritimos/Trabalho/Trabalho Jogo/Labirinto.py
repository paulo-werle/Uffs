# Alunos:
'''Nicole Ribas // nicole.r.abreu24@gmail.com
Paulo Werle // pauloeduardo840@gmail.com'''

#Descrição

''' Este é um jogo de Labirinto, aonde voçe é a bolinha vermelha, seu unico Objetivo é chegar na porta azul
porem todas as paredes do labirinto estao infectadas com um Super Veneno, CUIDADO, NAO ENCOSTE-SE NAS PAREDES'''

import turtle

#POSIÇÃO INICIAL
x=[-350]
y=[245]

#CANETAS
jogador = turtle.Turtle(shape = "circle")
labirinto = turtle.Turtle(shape = "turtle")
lab = turtle.Turtle()

#FUNÇOES:

def Home(a,b): #TELA
	
	turtle.onscreenclick(None)
	turtle.clear()
	turtle.resetscreen()
	
	#POSIÇÃO INICIAL
	x[0] = -350
	y[0] = 245
	
	#Tela;
	tela = turtle.Screen()
	tela.setup(900, 650) #Tamanho da tela
	tela.bgcolor("black")
	tela.title("Bem-Vindo ao Labirinto!!!")
	turtle.color("white")
	turtle.hideturtle()
	turtle.clear()
	turtle.pu()
	
	turtle.pu()
	turtle.goto(-50,0)
	turtle.write("JOGAR",font=("Arial",25,"normal"))
	turtle.pu()
	turtle.goto(-150,-150)
	turtle.write('''OBS: Este é um Jogo de Labirinto,
	Para ir para a frente use a Tecla: W
	Para virar-se para a direita use a Tecla: D
	Para virar-se para a Esquerda use a Tecla: A  ''',font=("Arial",15,"normal"))
	turtle.pu()
	
	turtle.onscreenclick(mapa)
	turtle.mainloop()
	
def mapa(a,b): #LABIRINTO
	turtle.onscreenclick(None)
	turtle.clear()
	
	#Caneta Cinza;
	labirinto.setposition(0,0)
	labirinto.ht( ) #Deixa invisível a ponta da caneta
	labirinto.pensize(10) #Tamanho
	labirinto.speed(0) #Velocidade
	labirinto.color ("grey")

	#Posição inicial da caneta Cinza.
	labirinto.penup() 
	labirinto.setposition(-375,275)
	labirinto.pendown()
	#--------------------------#

	#Limite da tela do jogo.
	for i in range(2):
		labirinto.forward(750)
		labirinto.right(90)
		labirinto.forward(550)
		labirinto.right(90)
	#--------------------------#

	#Caneta azul p/ a saída.
	lab.setposition(0,0)
	lab.ht()
	lab.pensize(5) #Tamanho
	lab.speed(0) #Velocidade
	lab.color ("blue")

	#Posição inicial da caneta azul.
	lab.penup()
	lab.setposition(362,-262)
	lab.left(90)
	lab.pendown()

	#Saída.
	lab.color("blue","blue")
	lab.begin_fill()
	for i in range(4):
		lab.forward(25)
		lab.left(90)	
	lab.end_fill()
	#--------------------------#

	#--------------------------#

	#Traços Verticais 
	for j in range(7):
		labirinto.penup()
		labirinto.forward(50)
		labirinto.right(90)
		labirinto.forward(50)
		labirinto.pendown()
		labirinto.forward(50)

		for i in range(4):
			labirinto.penup()
			labirinto.forward(50)
			labirinto.pendown()
			labirinto.forward(50)
			
		labirinto.penup()
		labirinto.forward(50)
		labirinto.left(90)
		labirinto.forward(50)
		labirinto.left(90)
		labirinto.pendown()
		labirinto.forward(50)

		for i in range(5):
			labirinto.penup()
			labirinto.forward(50)
			labirinto.pendown()
			labirinto.forward(50)
		
		labirinto.right(90)
	#--------------------------#

	#Segunda linha.
	labirinto.penup()
	labirinto.forward(50)
	labirinto.right(90)
	labirinto.forward(100)
	labirinto.right(90)

	#Traços horizontais da segunda linha
	labirinto.forward(50)
	labirinto.pendown()
	labirinto.forward(150)

	for i in range(3):
		labirinto.penup()
		labirinto.forward(50)
		labirinto.pendown()
		labirinto.forward(50)

	labirinto.forward(100)
	labirinto.penup()
	labirinto.forward(50)
	labirinto.pendown()
	labirinto.forward(50)
	labirinto.penup()
	labirinto.forward(50)
	#--------------------------#

	#Desce até a 4ª linha.
	labirinto.left(90)
	labirinto.forward(100)
	labirinto.left(90)

	#Traços da 4ª linha.
	labirinto.pendown()
	labirinto.forward(50)

	for i in range(7):
		labirinto.penup()
		labirinto.forward(50)
		labirinto.pendown()
		labirinto.forward(50)
	#--------------------------#

	#Desce até a última linha.
	labirinto.penup()
	labirinto.right(90)
	labirinto.forward(300)
	labirinto.right(90)

	#Mudanças na última linha.
	labirinto.forward(100)
	labirinto.pendown()
	labirinto.forward(50)
	labirinto.penup()
	labirinto.forward(250)
	labirinto.pendown()
	labirinto.forward(50)
	labirinto.penup()
	labirinto.forward(150)
	#--------------------------#

	#Sobe para a penúltima linha, fazendo um traço em diagonal.
	labirinto.right(45)
	labirinto.pendown()
	labirinto.forward(71)

	#Mudanças na penúltima linha
	labirinto.left(45)
	labirinto.forward(50)
	labirinto.penup()
	labirinto.right(180)
	labirinto.forward(200)

	for i in range(3):
		labirinto.pendown()
		labirinto.forward(50)
		labirinto.penup()
		labirinto.forward(50)
	#--------------------------#

	#Sobe para a oitava -antepenúltima- linha, fazendo um traço na diagonal.
	labirinto.left(45)
	labirinto.pendown()
	labirinto.forward(71)
	#--------------------------#

	#Desce p/ a nona linha de novo.
	labirinto.penup()
	labirinto.right(135)
	labirinto.forward(50)

	#Traço na nona linha.
	labirinto.left(90)
	labirinto.pendown()
	labirinto.forward(100)
	#--------------------------#

	#Virando p/ 7ª linha.
	labirinto.penup()
	labirinto.left(90)
	labirinto.forward(100)
	labirinto.left(45)

	#Traço na diagonal p/ 6ª linha.
	labirinto.pendown()
	labirinto.forward(70)

	#Virando na 6ª linha.
	labirinto.left(45)

	#Traços da 6ª linha.
	labirinto.forward(51)

	labirinto.penup()
	labirinto.forward(50)
	labirinto.pendown()
	labirinto.forward(50)

	labirinto.penup()
	labirinto.forward(100)
	labirinto.pendown()
	labirinto.forward(50)

	labirinto.penup()
	labirinto.forward(200)
	labirinto.pendown()
	labirinto.forward(50)

	labirinto.penup()
	labirinto.forward(50)
	labirinto.pendown()
	labirinto.forward(50)
	#--------------------------#

	#Sobe p/ 5ª linha.
	labirinto.penup()
	labirinto.right(90)
	labirinto.forward(50)
	labirinto.right(90)

	#Traços na 5ª linha.
	labirinto.forward(100)
	labirinto.pendown()
	labirinto.forward(150)
	labirinto.penup()
	labirinto.forward(50)
	labirinto.pendown()
	labirinto.forward(100)
	labirinto.penup()
	labirinto.forward(100)
	labirinto.pendown()
	labirinto.forward(150)
	#--------------------------#

	#Desce p/ 6ª linha, fazendo uma linha na diagonal.
	labirinto.right(45)
	labirinto.forward(70)

	#Continua na 6ª linha.
	labirinto.penup()
	labirinto.left(45)
	labirinto.forward(50)
	#--------------------------#

	#Sobe p/ 4ª linha.
	labirinto.left(90)
	labirinto.forward(100)
	labirinto.left(45)
	#--------------------------#

	#Sobe p/ a 3ª linha, fazendo uma linha na diagonal.
	labirinto.pendown()
	labirinto.forward(70)

	#Percorre a 3ª linha.
	labirinto.left(45)
	labirinto.penup()
	labirinto.forward(500)

	#Traço na 3ª linha.
	labirinto.pendown()
	labirinto.forward(50)
	labirinto.penup()
	labirinto.forward(50)
	#--------------------------#

	#Vira p/ 2ª linha e traça uma linha na diagonal.
	labirinto.pendown()
	labirinto.right(135)
	labirinto.forward(70)
	#--------------------------#

	#Desce p/ 7ª linha.
	labirinto.penup()
	labirinto.left(135)
	labirinto.forward(150)
	labirinto.left(90)
	labirinto.forward(250)
	labirinto.left(90)
	labirinto.forward(50)

	#Traço na 7ª linha.
	labirinto.pendown()
	labirinto.forward(50)
	labirinto.penup()
	labirinto.forward(100)
	labirinto.pendown()

	#Sobe com um traço na diagonal p/ 6ª linha.
	labirinto.left(45)
	labirinto.forward(70)

	#Volta p/ 7ª linha com um traço na diagonal.
	labirinto.right(90)
	labirinto.forward(70)

	#Continua na 7ª linha fzd um traço.
	labirinto.penup()
	labirinto.left(45)
	labirinto.forward(101)
	labirinto.pendown()
	labirinto.forward(50)
	#--------------------------#

	#Vira e desce p/ 8ª linha.
	labirinto.penup()
	labirinto.right(90)
	labirinto.forward(50)

	#Sobe p/ 7ª linha com uma linha diagonal.
	labirinto.pendown()
	labirinto.left(135)
	labirinto.forward(70)

	#Desce p/ 8ª linha.
	labirinto.penup()
	labirinto.right(135)
	labirinto.forward(50)
	labirinto.right(90)
	labirinto.forward(100)

	#Traço na 8ª linha.
	labirinto.pendown()
	labirinto.forward(49)

	#Desce p/ 9ª linha.
	labirinto.penup()
	labirinto.forward(100)
	labirinto.left(90)
	labirinto.forward(49)

	#Sobe p/ 8ª, traçando uma linha na diagonal.
	labirinto.pendown()
	labirinto.right(135)
	labirinto.forward(71)

	#Traço final na 8ª linha.
	labirinto.left(45)
	labirinto.forward(100)
	
	Jogador()

	turtle.done()

def Jogador(): #JOGADOR
	
	#Caneta verde p/ o jogador. 
	jogador.pensize(20) #Tamanho
	jogador.speed(0) #Velocidade
	jogador.color ("red")

	#Posição inicial da caneta verde.
	jogador.penup()
	jogador.right(90)

	move()
	turtle.done()
	
def move(): #SE MOVER
	for i in range(10000):
		jogador.setposition(x[0],y[0])
		turtle.onkey(u,"w")
		turtle.onkey(l,"a")
		turtle.onkey(r,"d")
		turtle.listen()
		
		ganhar_perder()
		
		jogador.setposition(x[0],y[0])
		
def ganhar_perder():#GANHAR OU PERDER
	if x[0] >= 361 or x[0] <= -361 or y[0] >= 264 or y[0] <= -264:
		gameover()

	#LINHAS VERTICAIS:
	#1ª linha vertical de paredes.
	elif x[0] >= -335 and x[0] <= -320 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= -335 and x[0] <= -320 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= -335 and x[0] <= -320 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= -335 and x[0] <= -320 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= -335 and x[0] <= -320 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
	
	#2ª linha vertical de paredes.
	elif x[0] >= -285 and x[0] <= -261 and y[0] >= 210: 
		gameover()
	elif x[0] >= -285 and x[0] <= -261 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= -285 and x[0] <= -261 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= -285 and x[0] <= -261 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= -285 and x[0] <= -261 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= -285 and x[0] <= -261 and y[0] < -220:
		gameover()
	#Fim.	
	
	#3ª linha vertical de paredes.
	elif x[0] >= -235 and x[0] <= -220 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= -235 and x[0] <= -220 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= -235 and x[0] <= -220 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= -235 and x[0] <= -220 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= -235 and x[0] <= -220 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
		
	#4ª linha vertical de paredes.
	elif x[0] >= -185 and x[0] <= -161 and y[0] >= 210:
		gameover()
	elif x[0] >= -185 and x[0] <= -161 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= -185 and x[0] <= -161 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= -185 and x[0] <= -161 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= -185 and x[0] <= -161 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= -185 and x[0] <= -161 and y[0] < -220:
		gameover()
	#Fim.
	
	#5ª linha vertical de paredes.
	elif x[0] >= -135 and x[0] <= -120 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= -135 and x[0] <= -120 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= -135 and x[0] <= -120 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= -135 and x[0] <= -120 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= -135 and x[0] <= -120 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
	
	#6ª linha vertical de paredes.
	elif x[0] >= -85 and x[0] <= -61 and y[0] >= 210:
		gameover()
	elif x[0] >= -85 and x[0] <= -61 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= -85 and x[0] <= -61 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= -85 and x[0] <= -61 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= -85 and x[0] <= -61 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= -85 and x[0] <= -61 and y[0] < -220:
		gameover()
	#Fim.
	
	#7ª linha vertical de paredes.
	elif x[0] >= -35 and x[0] <= -20 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= -35 and x[0] <= -20 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= -35 and x[0] <= -20 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= -35 and x[0] <= -20 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= -35 and x[0] <= -20 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
	
	#8ª linha vertical de paredes.
	elif x[0] >= 15 and x[0] <= 35 and y[0] >= 210:
		gameover()	
	elif x[0] >= 15 and x[0] <= 35 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= 15 and x[0] <= 35 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= 15 and x[0] <= 35 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= 15 and x[0] <= 35 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= 15 and x[0] <= 35 and y[0] < -220:
		gameover()
	#Fim
	
	#9ª linha vertical de paredes.
	elif x[0] >= 65 and x[0] <= 80 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= 65 and x[0] <= 80 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= 65 and x[0] <= 80 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= 65 and x[0] <= 80 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= 65 and x[0] <= 80 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
		
	#10ª linha vertical de paredes.
	elif x[0] >= 115 and x[0] <= 135 and y[0] >= 210:
		gameover()
	elif x[0] >= 115 and x[0] <= 135 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= 115 and x[0] <= 135 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= 115 and x[0] <= 135 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= 115 and x[0] <= 135 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= 115 and x[0] <= 135 and y[0] < -220:
		gameover()	
	#Fim
	
	#11ª linha vertical de paredes.
	elif x[0] >= 165 and x[0] <= 180 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= 165 and x[0] <= 180 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= 165 and x[0] <= 180 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= 165 and x[0] <= 180 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= 165 and x[0] <= 180 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
	
	#12ª linha vertical de paredes.
	elif x[0] >= 215 and x[0] <= 235 and y[0] >= 210:
		gameover()
	elif x[0] >= 215 and x[0] <= 235 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= 215 and x[0] <= 235 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= 215 and x[0] <= 235 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= 215 and x[0] <= 235 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= 215 and x[0] <= 235 and y[0] < -220:
		gameover()	
	#Fim
	
	#13ª linha vertical de paredes.
	elif x[0] >= 265 and x[0] <= 280 and y[0] < 230 and y[0] >= 170:
		gameover()
	elif x[0] >= 265 and x[0] <= 280 and y[0] < 130 and y[0] >= 70:
		gameover()
	elif x[0] >= 265 and x[0] <= 280 and y[0] < 30 and y[0] >= -30:
		gameover()
	elif x[0] >= 265 and x[0] <= 280 and y[0] < -70 and y[0] >= -125:
		gameover()
	elif x[0] >= 265 and x[0] <= 280 and y[0] < -175 and y[0] >= -230:
		gameover()
	#Fim.
	
	#14ª linha vertical de paredes.
	elif x[0] >= 315 and x[0] <= 335 and y[0] >= 210:
		gameover()
	elif x[0] >= 315 and x[0] <= 335 and y[0] < 180 and y[0] >= 120:
		gameover()
	elif x[0] >= 315 and x[0] <= 335 and y[0] < 80 and y[0] >= 20:
		gameover()
	elif x[0] >= 315 and x[0] <= 335 and y[0] < -10 and y[0] >= -80:
		gameover()
	elif x[0] >= 315 and x[0] <= 335 and y[0] < -120 and y[0] >= -180:
		gameover()
	elif x[0] >= 315 and x[0] <= 335 and y[0] < -220:
		gameover()	
	#Fim
	
	#LINHAS HORIZONTAIS:
	#2ª linha horizontal.
	elif x[0] >= -335 and x[0] <= -261 and y[0] < 190 and y[0] >= 165:
		gameover()
	elif x[0] >= -235 and x[0] <= -61 and y[0] < 190 and y[0] >= 165:
		gameover()
	elif x[0] >= -35 and x[0] <= 35 and y[0] < 190 and y[0] >= 165:
		gameover()
	elif x[0] >= 65 and x[0] <= 135 and y[0] < 190 and y[0] >= 165:
		gameover()
	elif x[0] >= 165 and x[0] <= 335 and y[0] < 190 and y[0] >= 165:
		gameover()
	#Fim.	
	
	#3ª linha horizontal.
	elif x[0] >= -235 and x[0] <= -163 and y[0] < 140 and y[0] >= 115:
		gameover()
	#Fim.
		
	#4ª linha horizontal.
	elif x[0] >= -361 and x[0] <= -315 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= -285 and x[0] <= -220 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= -185 and x[0] <= -120 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= -85 and x[0] <= -20 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= 15 and x[0] <= 80 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= 115 and x[0] <= 180 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= 215 and x[0] <= 280 and y[0] < 90 and y[0] >= 65:
		gameover()
	elif x[0] >= 315 and x[0] <= 361 and y[0] < 90 and y[0] >= 65:
		gameover()
	#Fim.
	
	#5ª linha horizontal.
	elif x[0] >= -285 and x[0] <= -120 and y[0] < 40 and y[0] >= 15:
		gameover()
	elif x[0] >= -85 and x[0] <= 35 and y[0] < 40 and y[0] >= 15:
		gameover()
	elif x[0] >= 115 and x[0] <= 280 and y[0] < 40 and y[0] >= 15:
		gameover()
	#Fim.
	
	#6ª linha horizontal.
	elif x[0] >= -361 and x[0] <= -315 and y[0] < -10 and y[0] >= -35:
		gameover()
	elif x[0] >= -285 and x[0] <= -220 and y[0] < -10 and y[0] >= -35:
		gameover()
	elif x[0] >= -35 and x[0] <= 35 and y[0] < -10 and y[0] >= -35:
		gameover()
	elif x[0] >= 115 and x[0] <= 180 and y[0] < -10 and y[0] >= -35:
		gameover()
	elif x[0] >= 215 and x[0] <= 280 and y[0] < -10 and y[0] >= -35:
		gameover()
	#Fim.
	
	#7ª linha horizontal.
	elif x[0] >= -335 and x[0] <= -261 and y[0] < -60 and y[0] >= -91:
		gameover()
	elif x[0] >= 15 and x[0] <= 80 and y[0] < -60 and y[0] >= -91:
		gameover()
	#Fim.
	
	#8ª linha horizontal.
	elif x[0] >= -285 and x[0] <= -161 and y[0] < -110 and y[0] >= -141:
		gameover()
	elif x[0] >= -35 and x[0] <= 35 and y[0] < -110 and y[0] >= -141:
		gameover()
	#Fim.
	
	#9ª linha horizontal.
	elif x[0] >= -335 and x[0] <= -261 and y[0] < -160 and y[0] >= -191:
		gameover()
	elif x[0] >= -135 and x[0] <= -61 and y[0] < -160 and y[0] >= -191:
		gameover()
	elif x[0] >= -35 and x[0] <= 35 and y[0] < -160 and y[0] >= -191:
		gameover()
	elif x[0] >= 65 and x[0] <= 135 and y[0] < -160 and y[0] >= -191:
		gameover()
	elif x[0] >= 215 and x[0] <= 335 and y[0] < -160 and y[0] >= -191:
		gameover()
	#Fim.
	
	#10ª linha horizontal.
	elif x[0] >= -85 and x[0] <= -20 and y[0] < -210 and y[0] >= -241:
		gameover()
	elif x[0] >= 215 and x[0] <= 280 and y[0] < -210 and y[0] >= -241:
		gameover()
	#Fim.

	
	#Linhas Diagonais
	elif x[0] >= -275 and x[0] <= -250 and y[0] <= 175 and y[0] >= 150:
		gameover()
	elif x[0] >= -250 and x[0] <= -225 and y[0] <= 150 and y[0] >= 125:
		gameover()
		
	elif x[0] >= -275 and x[0] <= -250 and y[0] <= -200 and y[0] >= -225:
		gameover()
	elif x[0] >= -250 and x[0] <= -225 and y[0] <= -175 and y[0] >= -200:
		gameover()
		
	elif x[0] <= 375 and x[0] >= 350 and y[0] >= 100 and y[0] <= 125:
		gameover()
	elif x[0] <= 350 and x[0] >= 325 and y[0] >= 75 and y[0] <= 100:
		gameover()
		
	elif x[0] <= 325 and x[0] >= 300 and y[0] >= 0 and y[0] <= 25:
		gameover()
	elif x[0] <= 300 and x[0] >= 275 and y[0] >= -25 and y[0] <= 0:
		gameover()
	elif x[0] <= 325 and x[0] >= 300 and y[0] <= -50 and y[0] >= -25:
		gameover()
	elif x[0] <= 300 and x[0] >= 275 and y[0] >= -75 and y[0] >= -50:
		gameover()
	
	elif x[0] >= -125 and x[0] <= -100 and y[0] >= -50 and y[0] <= -25:
		gameover()
	elif x[0] >= -100 and x[0] <= -75 and y[0] >= -75 and y[0] <= -50:
		gameover()
	elif x[0] >= -175 and x[0] <= -150 and y[0] <= -25 and y[0] >= -50:
		gameover()
	elif x[0] >= -150 and x[0] <= -125 and y[0] <= -50 and y[0] >= -75:
		gameover()
	
	#Vencer			
	elif x[0]>= 337 and x[0] <= 362 and y[0]<= -237 and y[0]>= -262:
		vencer()
		

def u(): # ANDAR PRA FRENTE #UP
	jogador.pu()
	
	if jogador.heading() == 0:
		y[0] = y[0] + 0
		x[0] = x[0] + 10
	elif jogador.heading() == 90:
		y[0] = y[0] + 10
		x[0] = x[0] + 0
	elif jogador.heading() == 180:
		y[0] = y[0] + 0
		x[0] = x[0] - 10
	elif jogador.heading() == 270:
		y[0] = y[0] - 10
		x[0] = x[0] + 0
	elif jogador.heading() == 0:
		y[0] = y[0] + 0
		x[0] = x[0] + 10
		
	return x,y
	
def r():#VIRAR A DIREITA #RIGHT
	jogador.pu()
	jogador.right(90)
	
def l():#VIRAR A ESQUERDA #LEFT
	jogador.pu()
	jogador.left(90)
	
def posicao(): #POSIÇÕES
	
	if jogador.heading() == 0:
		y += 0
		x += 10
	elif jogador.heading() == 90:
		y += 10
		x += 0
	elif jogador.heading() == 180:
		y += 0
		x += -10
	elif jogador.heading() == 270:
		y += -10
		x += 0
	elif jogador.heading() == 0:
		y += 0
		x += 10
		
	return x,y
	
def gameover():#SE PERDER
    turtle.onscreenclick(None)
    turtle.speed(0)
    turtle.pu()
    jogador.clear()
    labirinto.clear()
    lab.clear()
    turtle.goto(-150,0)
    turtle.color("white")
    turtle.write("VOCÊ PERDEU",font=("Arial",25,"normal"))
    turtle.goto(-200,-50)
    turtle.write("Para começar novamente clique com o Mouse",font=("Arial",15,"normal"))
    
    turtle.onscreenclick(Home)
    turtle.mainloop()
    
def vencer():#SE GANHAR
	turtle.speed(0)
	turtle.pu()
	jogador.clear()
	labirinto.clear()
	lab.clear()
	for i in range(100):
		turtle.goto(-250,0)
		turtle.color("white")
		turtle.write("PARABÉNS, VOCÊ É FODA!!!! ",font=("Arial",25,"normal"))
		turtle.clear()
		turtle.write("PARABÉNS, VOCÊ É FODA!!!! ",font=("Arial",25,"normal"))
	turtle.mainloop()
	
#CODIGO PRINCIPAL

Home(x,y)

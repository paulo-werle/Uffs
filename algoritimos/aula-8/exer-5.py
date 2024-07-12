'''Escreva um programa que leia uma lista de 13 posições, sendo ela o gabarito de um teste de
loteria esportiva, contendo os valores 1 (coluna 1), 2 (coluna 2) e 3 (coluna do meio). Na sequência,
leia mais uma lista de 13 posições contendo uma aposta. Após isso, compare as listas, verificando o
número de acertos. No fim, escrever a quantidade de acertos, e se a aposta possuir 13 acertos,
acrescentar a mensagem: "GANHADOR, PARABÉNS".'''

gabarito = []
apostas = []
acertos = 0

print("Informe o Gabarito das apostas:")
for num in range(13):
	resposta = int(input())
	gabarito.append(resposta)
	
print("Informe as apostas")
for num in range(13):
	chute = int(input())
	apostas.append(chute)
	
for num in range(13):
	if gabarito[num] == apostas[num]:
		acertos+=1
		
print("Voçe acertou: {}".format(acertos))
if acertos == 13:
	print("GANHADOR, PARABÉNS")
	


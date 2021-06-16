'''Uma rainha requisitou os serviços de um monge e disse-lhe que pagaria qualquer preço. O
monge, necessitando de alimentos, indagou à rainha sobre o pagamento, se poderia ser feito com
grãos de trigo dispostos em um tabuleiro de xadrez (que possui 64 casas), de tal forma que o
primeiro quadro deveria conter apenas um grão e os quadros subsequentes, o dobro do quadro
anterior. Crie um algoritmo para calcular o total de grãos que o monge recebeu. Utilize um laço
FOR.'''

soma = 1
resultado = 1

for num in range(64):
	soma = soma * 2
	resultado += soma
	
print(resultado)

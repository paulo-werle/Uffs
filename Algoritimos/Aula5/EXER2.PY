'''Escreva um programa que, ao ser executado, apresente o menu inicial abaixo:
---Menu principal---
1- Boas vindas a CC
2- Primeiro programa
3- Condições
4- Repetições
0- Sair do programa
As opções 1, 2, 3 e 4 acima devem mostrar as seguintes mensagens:
1- Seja bem vindo ao curso de Ciência da Computação da UFFS
2- Alô Mundo em Python
3- IF, ELIF e ELSE
4- WHILE
0- Sair do programa utilizando o método exit()
Caso o usuário digite uma opção inválida, exiba a mensagem “Opção inválida” e mostre o menu
novamente.'''

while True:

	print("\n 1- Boas vindas a CC \n 2- Primeiro programa\n 3- Condições\n 4- Repetições\n 0- Sair do programa\n")

	opcao = int(input("Informe a Opção Desejada  \n"))

	while opcao != 1 and opcao != 2 and opcao != 3 and opcao != 4 and opcao != 0:
		print("Opção inválida")
		print("\n 1- Boas vindas a CC \n 2- Primeiro programa\n 3- Condições\n 4- Repetições\n 0- Sair do programa\n")
		opcao = int(input("Informe a Opção Desejada"))
		
	if opcao == 1 or opcao == 2 or opcao == 3 or opcao == 4 or opcao == 0:
		
		if opcao == 1:
			print("1- Seja bem vindo ao curso de Ciência da Computação da UFFS ")

		elif opcao == 2:
			print("2- Alô Mundo em Python ")
		
		elif opcao == 3:
			print("3- IF, ELIF e ELSE ")
		
		elif opcao == 4:
			print("4- WHILE ")
		
		elif opcao == 0:
			exit()

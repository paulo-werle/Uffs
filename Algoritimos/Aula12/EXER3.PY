'''Um aluno de uma turma pode ser representado pelos seguintes dados: matrícula, nota 1 e nota 2.
Faça um programa que leia 5 alunos, guardando seus dados em uma estrutura. Após ler cada aluno,
chame a função media_aluno(aluno), sendo que ela recebe uma variável do tipo estrutura aluno e
retorna a sua média ((nota 1+nota 2)/2), que deve ser impressa no código principal.'''

#ESTRUTURAS

class aluno:
	matricula=""
	nota1=0.0
	nota2=0.0

#FUNÇÃO

def media_aluno(aluninhos,i):
	media = (aluninhos[i].nota1 + aluninhos[i].nota2)/2
		
	return media

#CODIGO PRICIPAL

aluninhos = []
for i in range(5):
	a = aluno()
	a.matricula = input("Informe a matricula do Aluno:  ")
	a.nota1 = float(input("Informe sua Primera Nota:  "))
	a.nota2 = float(input("Informe sua Primera Nota:  "))
	print()
	aluninhos.append(a)
	
for i in range(5):
	media = media_aluno(aluninhos,i)

	print("A Matricula do Aluno é {}, e sua media é {}".format(aluninhos[i].matricula,media))

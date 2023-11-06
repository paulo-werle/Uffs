// 3. Faça um programa que lê o número de matrícula, o nome e o IAA de um aluno e grava ao final de um arquivo em formato binário. 
// Após a gravação, reposicione o cursor no início do arquivo e exiba a lista de todos os alunos.
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int matricula;
  char nome[50];
  float iaa;
} Aluno;

int main(){

  // Abre arquivo para ler e gravar em binario
  FILE *archive = fopen("output.out", "r+b");
  if(archive == NULL){
    printf("Erro ao abrir o arquivo!");
    exit(1);
  }

  // Coloca no fim do arquivo
  fseek(archive, 0, SEEK_END);

  Aluno aluno;

  // Le dados para gravar no arquivo
  printf("Informe a matricula: ");
  scanf("\n%d", &aluno.matricula);

  printf("Informe o primeiro nome: ");
  scanf("\n%s", aluno.nome);

  printf("Informe o iaa: ");
  scanf("\n%f", &aluno.iaa);

  // Grava informação no arquivo
  fwrite(&aluno, sizeof(Aluno), 1, archive);
  
  // Retorna para o inicio do arquivo
  fseek(archive, 0, SEEK_SET);

  // Percorre arquivo para imprimir
  while( fread(&aluno, sizeof(Aluno), 1, archive) ){
  
    // Imprime dados do arquivo
    printf("%d - %s - %.2f\n", aluno.matricula, aluno.nome, aluno.iaa);
  }

  // Fecha arquivo
  fclose(archive);

  return 0;
}
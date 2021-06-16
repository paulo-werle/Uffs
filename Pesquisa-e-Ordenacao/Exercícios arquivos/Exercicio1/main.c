// 1. Faça um programa que lê o conteúdo de um arquivo de texto e cria outro arquivo com o mesmo conteúdo, 
// mas com todas as letras minúsculas convertidas para maiúsculas.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(){
  int i;
  char text[500];

  // Abre arquivo para leitura
  FILE *read_archive = fopen("input.txt", "r");
  if(read_archive == NULL){
    printf("Erro ao abrir o arquivo!");
    exit(1);
  }

  // Abre o arquivo de escrita
  FILE *write_archive = fopen("output.txt", "w");
  if(write_archive == NULL){
    printf("Erro ao abrir o arquivo!");
    exit(1);
  }

  // Le arquivo e atribui valor mauisculo ao array
  i = 0;
  while( !feof(read_archive) ){
    fputc( toupper( fgetc(read_archive) ), write_archive );
    i++;
  }

  // Fecha arquivo
  fclose(read_archive);
  fclose(write_archive);

  return 0;
}
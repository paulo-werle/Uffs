#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int conta_vogaischar string[0])
int contaVogais(char *string){

  // Inicia variaveis
  int i, count = 0;
  int stringLenght = strlen(string);
  
  // Percorre para contar vogais
  for (i = 0; i <= stringLenght; i++){
    if (
      string[i] == 'a' ||
      string[i] == 'e' ||
      string[i] == 'i' ||
      string[i] == 'o' ||
      string[i] == 'u' 
    
    ){
      count ++;
    }
  }
  return count;
}

// char &string[0] elimina_vogais(char &string[0]);
char *eliminaVogais(char *string){
  // Inicia variaveis
  int count = 0, position = 0;
  char *stringCopy = malloc(sizeof(string));

  // Percorre para contar vogais
  while (string[count] != '\0' ){
    if (
      string[count] != 'a' && 
      string[count] != 'e' && 
      string[count] != 'i' && 
      string[count] != 'o' && 
      string[count] != 'u' 
    ){
      stringCopy[position] = string[count];
      position++; 
    }
    count++;
  }

  return stringCopy;
}


int main(){

  // Inicia variaveis
  int quantity = 0;
  char string[] = "isto eh uma string";
  char *stringCopy;

  // Chama funções
  quantity = contaVogais(string);
  stringCopy = eliminaVogais(string);

  // Imprime resultados
  printf("Quantidade de vogais: %d \n", quantity);
  printf("A string original: %s \n", string);
  printf("A string sem vogais: %s \n", stringCopy);

  return 0;
}
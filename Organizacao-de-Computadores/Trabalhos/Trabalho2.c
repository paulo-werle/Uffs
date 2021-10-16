#include <stdio.h>
#include <stdlib.h>

// Configurações do programa

// Número de células na MP: 128;
#define CELL 128
// Tamanho do bloco: 4 células;
#define BLOCK_SIZE 4
// Número de linhas na cache: 8;
#define LINES_IN_CACHE 8

// Structs
struct block
{ // Bloco de memoria
  
  char color[BLOCK_SIZE];
};
typedef struct block Block;

struct cache
{ //Memoria cache
  
  Block blocks[32]
};
typedef struct cache Cache;


int main(){

  printf("Teste de programa\n");

  return 0;
}
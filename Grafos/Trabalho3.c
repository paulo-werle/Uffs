#include <stdio.h>
#include <stdlib.h>

// Define o tamanho da matriz de adjacencia
#define SIZE 5

int main(){
  // Inicia variaveis
  int from, to, location, count, value, go_to;
  int progress_counter = 0;

  // Grafo orientado
  int data[SIZE][SIZE] = {
    { 0, 1, 0, 0, 0 },
    { 0, 0, 2, 0, 0 },
    { 1, 0, 0, 0, 2 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
  };
  
  printf("Escolha o nodo de origem, OBS: 1..%d: ", SIZE);
  scanf("%d", &from);
  from--;

  printf("Escolha o nodo de destino, OBS: 1..%d: ", SIZE);
  scanf("%d", &to);
  to--;

  // Define localização atual como origem
  location = from;

  while(location != to){

    // Para caso estiver cansado
    if (progress_counter >= SIZE){
      printf("Cansei, impossível fazer com Guloso \n");
      break;
    }

    // Define valor como 0
    value = 0;

    printf("As opções disponiveis nessa interação:\n");
    // Percorre para achar maior elemento, e que não seja ele mesmo
    for ( count = 0; count < SIZE; count++){
      if (data[location][count] > value && location != count){
        value = data[location][count];
        go_to = count;
      }

      if (data[location][count] > 0 && location != count){
        printf("\t %d > %d, Valor da arresta: %d \n", (location + 1), (count + 1), data[location][count]);
      }
    }

    // Caso não poder mais avançar
    if (value != 0){
      printf("\n- Escolhemos: %d -> %d \n\n", (location + 1), (go_to + 1));
      location = go_to;
    } else {
      printf("\n -Impossível com Guloso \n");
      break;
    }
    
    progress_counter++;
  }

	return 0;
}
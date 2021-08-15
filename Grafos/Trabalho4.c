#include <stdio.h>
#include <stdlib.h>

// Define valores
#define SIZE 8
#define INFINITE 1000

// Define estrutura para armazenar dados 
struct data {
  int visited[SIZE];
  int value[SIZE];
  int previous[SIZE];
};
typedef struct data Data;

Data *initData( int initialVertex ) {
  // Inicia variaveis
  Data *data = malloc (sizeof(Data));
  int i;

  // Atribui valores
  for (i = 0; i < SIZE; i++){

    // Inicia valores comuns
    data->visited[i] = 0;
    data->previous[i] = -1;
    
    // Define 0 para o vertice inicial e INFINITE para os demais
    if ( i == initialVertex ){
      data->value[i] = 0;
    } else {
      data->value[i] = INFINITE;
    }

  }
  
	return data;
}

void printData( Data *data ) {
  // Inicia variaveis
  int i;

  // Atribui valores
  printf("Vert.\t| Vis.\t| Valor\t| Ant.\n");
  for (i = 0; i < SIZE; i++){
    printf("%d\t| %d\t| %d\t| %d\n", i, data->visited[i], data->value[i], data->previous[i]);
  }
  printf("\n");
}

void analyzeDataByDijkstra( int graph[SIZE][SIZE], Data *data, int curVert ) {
  int i, sumValue, nextVertex, minValue;

  // Cria laço enquanto o curVert não for um elemento visitado 
  while ( !data->visited[curVert] ){

    // Inicia variaveis utilizados no loop
    minValue = INFINITE;

    // Coloca como visitado e imprime o vertice
    data->visited[curVert] = 1;
    printf("Visitando %d\n\n", curVert);

    // Percorre vertices adjacentes
    for (i = 0; i < SIZE; i++) {
 
      // Faz a soma entre o valor até o curVert e o vertice adjacente
      sumValue = data->value[curVert] + graph[curVert][i];

      // Verefica se a soma é menor que o valor presente, e se possui uma arresta
      if ( sumValue < data->value[i] && graph[curVert][i] != 0 ){
        
        // Atualiza valores
        data->value[i] = sumValue;
        data->previous[i] = curVert;
      }

    }

    // Imprime dados coletados
    printf("Estado atual\n");
    printData(data);

    // Percorre dados procurando o proximo
    for (i = 0; i < SIZE; i++) {

      // Verefica se é o menor valor, e se ainda não foi visitado
      if (data->value[i] < minValue && !data->visited[i]){
        nextVertex = i;
        minValue = data->value[i];
      }
    }

    // Atualiza vertice atual
    curVert = nextVertex;
  }
}

int main(){

  int initialVertex;
  int graph[SIZE][SIZE] = {
    { 0, 4, 0, 0, 0, 0, 0, 0 },
    { 4, 0, 0, 3, 0, 9, 1, 0 },
    { 0, 0, 0, 0, 2, 0, 3, 0 },
    { 0, 3, 0, 0, 0, 8, 0, 5 },
    { 0, 0, 2, 0, 0, 0, 0, 0 },
    { 0, 8, 0, 8, 0, 0, 1, 0 },
    { 0, 1, 3, 0, 0, 1, 0, 3 },
    { 0, 0, 0, 5, 0, 0, 3, 0 },
  };

  // Define vertice inicial
  printf("informe o vertice inicial: ");
  scanf("%d", &initialVertex);

  // Iniciando dados
  Data *data = initData(initialVertex);

  // Chama função Dijkstra
  analyzeDataByDijkstra(graph, data, initialVertex);
  
	return 0;
}
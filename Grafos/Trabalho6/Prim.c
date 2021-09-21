#include <stdio.h>
#include <stdlib.h>

// Define valores
#define SIZE 8
#define INFINITE 1000

// Arresta
typedef struct _edge {
	int origem;
	int destino;
	int value;
} Edge;

// Lista de arresta
typedef struct _list_edge {
	Edge *edge;
	struct _list_edge *next;
} ListEdge;

// Define estrutura para armazenar dados 
struct data {
  int visited[SIZE];
  int value[SIZE];
  int previous[SIZE];
  ListEdge *list_edge;
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

// Inserir arresta
ListEdge *insertEdge (ListEdge *list_edge, int origem, int destino, int valor){

	ListEdge *aux,*newElement = malloc (sizeof(ListEdge));
  newElement->edge = malloc (sizeof(Edge));
  newElement->edge->origem = origem;
  newElement->edge->destino = destino;
  newElement->edge->value = valor;

	if (list_edge == NULL){
		list_edge = newElement;
	}else{
		aux = list_edge;
		while ( aux->next != NULL){ 
			aux = aux->next;
		}
		aux->next = newElement;
		newElement->next = NULL;		
	}

	return list_edge;
}

// Prim
void prim( int graph[SIZE][SIZE], Data *data, int curVert ) {
  int i, sumValue, nextVertex, minValue, origem, destino;

  // Cria laço enquanto o curVert não for um elemento visitado 
  while ( !data->visited[curVert] ){

    // Inicia variaveis utilizados no loop
    minValue = INFINITE;

    // Coloca como visitado e imprime o vertice
    data->visited[curVert] = 1;
    printf("Visitando %d\n\n", curVert);

    // Percorre vertices adjacentes
    for (i = 0; i < SIZE; i++) {
 
      // Faz curVert e o vertice adjacente ser sumValue 
      sumValue = graph[curVert][i];

      // Verefica se a soma é menor que o valor presente, e se possui uma arresta
      if ( sumValue < data->value[i] && graph[curVert][i] != 0 ){
        
        // Atualiza valores
        data->value[i] = sumValue;
        data->previous[i] = curVert;

        // Adiciona dados no caminho
        data->list_edge = insertEdge( data->list_edge, curVert, i, graph[i][curVert] );
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

// Faz a soma do caminho
void sumWay( ListEdge *head) {
	ListEdge *aux = head;
	int sumValue = 0;

	printf("Resultado:\n\t");
	while (aux != NULL){
		// Imprime 
		printf("(%d, %d), ", aux->edge->origem, aux->edge->destino);
		
		// Acrescenta valor
		sumValue += aux->edge->value;

		// Define proximo
		aux= aux->next;
	}
	printf("\n\tSoma: %d\n", sumValue);
}

// Principal
int main(){

  int initialVertex;
  int graph[SIZE][SIZE] = {
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 3, 4, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 5 },
    { 0, 0, 3, 0, 0, 0, 0, 0 },
    { 0, 0, 4, 0, 0, 0, 0, 5 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 5, 0, 5, 0, 0 },
  };

  // Define vertice inicial
  printf("informe o vertice inicial: ");
  scanf("%d", &initialVertex);

  // Iniciando dados
  Data *data = initData(initialVertex);

  // Chama função Dijkstra
  prim(graph, data, initialVertex);

  // Soma o caminho
  sumWay(data->list_edge);
  
	return 0;
}
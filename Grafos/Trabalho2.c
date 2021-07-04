#include <stdio.h>
#include <stdlib.h>

// Define o tamanho da matriz de adjacencia
#define SIZE_1 5
#define SIZE_2 5

// Define estrutura para armazenar a matriz
typedef struct {
	int adjacents[SIZE_1][SIZE_2];
} Graph;

// Definição dos Methodos
Graph  *graphInit(){
	Graph *graph = malloc (sizeof(Graph));
	return graph;
}
Graph *graphInsertData( Graph *graph, int data[SIZE_1][SIZE_2] ){
	
	// Iniciando valores
	int count_1, count_2;

	// Percorrendo valores para inserir no grafo
	for (count_1 = 0; count_1 < SIZE_1; count_1++) {
		for (count_2 = 0; count_2 < SIZE_2; count_2++) {
			graph->adjacents[count_1][count_2] = data[count_1][count_2];
		}
	}

	return graph;
}
void graphNotOriented( Graph *graph ){
	
	// Iniciando valores
	int count_1, count_2, total_count; 

	// Percorrendo valores para imprimir
	for (count_1 = 0; count_1 < SIZE_1; count_1++) {
		total_count = 0;
		
		for (count_2 = 0; count_2 < SIZE_2; count_2++) {
			if (graph->adjacents[count_1][count_2] != 0) {
				total_count++;
			}
		}

		printf("D(%d) = %d \n", (count_1 + 1), total_count);
	}
}
void graphOriented( Graph *graph ){
	
	// Iniciando valores
	int count_1, count_2, out_count, in_count; 

	// Percorrendo valores para imprimir
	for (count_1 = 0; count_1 < SIZE_1; count_1++) {
		out_count = 0, in_count = 0;
		
		for (count_2 = 0; count_2 < SIZE_2; count_2++) {
			if (graph->adjacents[count_1][count_2] > 0) {
				out_count++;
			}
			if (graph->adjacents[count_2][count_1] > 0) {
				in_count++;
			}
		}

		// Imprime valores de entrada
		if ( out_count == 0){
			printf("D(%d) é sumidouro \n", (count_1 + 1));
		} else {
			printf("D-Ouput(%d) = %d \n", (count_1 + 1), out_count);
		}

		// Imprime valores de saida
		if ( in_count == 0){
			printf("D(%d) é fonte \n", (count_1 + 1));
		} else {
			printf("D-Input(%d) = %d \n", (count_1 + 1), in_count);
		}
		
		printf("\n");
	}
}
void graphPrint( Graph *graph ){
	
	// Iniciando valores
	int option;

	printf("Your graph is oriented?\n \t 1:No, \n \t 2:Yes \n");
	scanf("%d", &option);

	if (option == 1)
	{ // Caso não for um grafo orientado
		graphNotOriented(graph);
	}
	else if(option == 2)
	{ // Caso for um grafo orientado
		graphOriented(graph);
	}
	else 
	{ // Caso a entrada for outra
		printf("Invalid option");
	}
}

int main(){

	// Grafo não orientado
  // int data[SIZE_1][SIZE_2] = {
  //   { 0, 0, 1, 0, 0 },
  //   { 0, 0, 1, 0, 0 },
  //   { 1, 1, 0, 1, 1 },
  //   { 0, 0, 1, 0, 1 },
  //   { 0, 0, 1, 1, 0 },
  // };

	// Grafo orientado
  int data[SIZE_1][SIZE_2] = {
    { 0, 0, 1, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 0 },
  };

	
	// Iniciando Grafo
	Graph *graph = graphInit();

	// Inserindo valores no grafo
	graph = graphInsertData(graph, data);

	graphPrint(graph);

	return 0;
}
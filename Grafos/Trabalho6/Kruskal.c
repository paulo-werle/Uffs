#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

// ---------- Estruturas ----------
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

// Grafo
typedef struct {
	ListEdge *list_edge;
} Graph;

// Dados
typedef struct {
	int root[SIZE];
	ListEdge *list_edge;
} Data;
// ---------- Estruturas ----------

// ---------- Funções ----------
// Iniciar grafo
Graph  *graphInit(){
	Graph *graph = malloc (sizeof(Graph));
	graph->list_edge = NULL;
	return graph;
}

// Inicia dados
Data *initData() {

	// Inicia variaveis
  	Data *data = malloc (sizeof(Data));
	int count;

	// Percorre dados para iniciar valores
	for ( count = 0; count < SIZE; count++ ){ 
	
		// Coloca valor inicial na raiz  
		data->root[count] = -1;
  	}
  
	return data;
}

// Inserir arresta ordenadamente
ListEdge *insertSortedEdge ( ListEdge *list_edge, int origem, int destino, int value){
	
	// Cria variaveis auxiliares
	ListEdge *aux, *ant = NULL;
	ListEdge *newElement = malloc ( sizeof(ListEdge) );

	// Cria arresta
	newElement->edge = malloc ( sizeof(Edge) );
	newElement->edge->origem = origem;
	newElement->edge->destino = destino;
	newElement->edge->value = value;

	// Define proximo como null
	newElement->next = NULL;

	// Manipula lista
	aux = list_edge;

	// Percorre enquanto não for maior que o valor e não ser o final
	while ( aux != NULL && aux->edge->value <= value ) {
		ant = aux;
		aux = aux->next;
	}

	// Insere primeiro
	if (ant == NULL) {
		newElement->next = list_edge;
		list_edge = newElement;
	
	// Insere no meio
	} else {
		newElement->next = ant->next;
		ant->next = newElement;
	}

	return list_edge;
}

// Inserir arresta
ListEdge *insertEdge (ListEdge *list_edge, Edge *edge){

	ListEdge *aux,*newElement = malloc (sizeof(ListEdge));
	newElement->edge = edge;

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

// Imprimir arrestas
void printListEdge(ListEdge *head){
	ListEdge *aux = head;

	printf("Caminho:");
	while (aux != NULL){
		printf("(%d, %d), ", aux->edge->origem, aux->edge->destino);
		aux= aux->next;
	}
	printf("\n\n");
	
}

// Imprime dados
void printData( Data *data ) {
	int count;

	printf("indi -> |");
	for ( count = 0; count < SIZE; count++ ) {
		printf(" %d \t|", count);
	}
	printf("\n");

	printf("raiz -> |");
	for ( count = 0; count < SIZE; count++ ) {
		printf(" %d \t|", data->root[count] );
	}
	printf("\n\n");
}

// Kruskal
void kruskal( ListEdge *list_edge, Data *data ) {
	int origin, destination;
	ListEdge *aux = list_edge;

	// Percorre enquanto haver arrestas na lista
	while ( aux != NULL ){

		// Imprimindo mensagem
		printf("\n------ Estado atual -------\n");
		
		// Verefica raiz diretamente
		origin = aux->edge->origem;
		destination = aux->edge->destino;

		// Caso item tiver raiz em outro vertice
		if ( data->root[origin] >= 0 ) {
			origin = data->root[origin];
		}
		if ( data->root[destination] >= 0 ) {
			destination = data->root[destination];
		}

		// Imprime qual aresta está sendo explorada
		printf("Visitando: (%d, %d) - %d\n\n", aux->edge->origem, aux->edge->destino, aux->edge->value );

		if ( origin != destination ) {

			if ( data->root[origin] < data->root[destination] ) {
				// Atribui dados
				data->root[origin] += data->root[destination];
				data->root[destination] = origin;

			} else {
				// Atribui dados
				data->root[destination] += data->root[origin];
				data->root[origin] = destination;
			}

			// Insere nos dados visitados
			data->list_edge = insertEdge(data->list_edge, aux->edge);
		} 
		// else {
		// 	printf("Iria causar um loop\n");
		// }
		
		// Imprime dados e caminho
		printData(data);
		printListEdge(data->list_edge);

		// Vai para o proximo elemento
		aux = aux->next;
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
	int count;

	Graph *graph = graphInit();
	Data *data = initData();

	// Insere arrestas
	graph->list_edge = insertSortedEdge(graph->list_edge, 0, 1, 5);
	graph->list_edge = insertSortedEdge(graph->list_edge, 0, 3, 3);
	graph->list_edge = insertSortedEdge(graph->list_edge, 1, 3, 8);
	graph->list_edge = insertSortedEdge(graph->list_edge, 1, 5, 3);
	graph->list_edge = insertSortedEdge(graph->list_edge, 2, 5, 7);
	graph->list_edge = insertSortedEdge(graph->list_edge, 5, 6, 2);
	graph->list_edge = insertSortedEdge(graph->list_edge, 5, 7, 3);
	graph->list_edge = insertSortedEdge(graph->list_edge, 6, 7, 4);

	// Analizando
	kruskal(graph->list_edge, data);

	// Faz a soma do caminho
	sumWay(data->list_edge);

	return 0;
}
#include <stdio.h>
#include <stdlib.h>

/*
 Estrutura responsável por armazenar os vértices. Struct Vertex armazena o véritce em si
	Já ListVertex é uma lista encadeada dos vértices.
*/
struct _vertex 
{
	int value;
};
typedef struct _vertex Vertex;

struct _list_vertex
{
	Vertex *v;
	struct _list_vertex *next;
};
typedef struct _list_vertex ListVertex;

/*
 Estrutura responsável por armazenar as arestas. Struct Edge armazena a aresta, 
 	com vértice de origem e vértice de destino
Já ListEdge é uma lista simplesmente encadeada das arestas.
*/
struct _edge 
{
	Vertex *origem;
	Vertex *destino;
};
typedef struct _edge Edge;
struct _list_edge
{
	Edge *e;
	struct _list_edge *next;
};
typedef struct _list_edge ListEdge;

/*O Grafo, constituido da lista de vértices e arestas
	V-> Armazena a cabeça da lista dos vértices
	E-> Armazena a cabeça da lista de arestas
*/
typedef struct {
	ListVertex *V; //lista de vértices
	ListEdge *E; //Lista de arestas
} Graph;

Graph  *graphInit(){
	Graph *graph = malloc (sizeof(Graph));
	graph->E = NULL;
	graph->V = NULL;
	return graph;
}

//Funções Lista Vertices
Vertex *findVertex (ListVertex *head, int value){
  ListVertex *list_aux = head;
  Vertex *vertex_aux;

	while (list_aux != NULL){
    if (list_aux->v->value == value){
      vertex_aux = list_aux->v;
    }

		list_aux = list_aux->next;
	}

  return vertex_aux;
}

ListVertex *insertVertex (ListVertex *head, int value){
	ListVertex *aux,*newElement = malloc (sizeof(ListVertex));
	newElement->v = malloc (sizeof(Vertex));
	newElement->v->value = value;

	if (head == NULL){
		head = newElement;
	}else{
		aux = head;
		while ( aux->next != NULL){ 
			aux=aux->next;
		}
		aux->next = newElement;
		newElement->next = NULL;		
	}

	return head;
}

void printListVertex(ListVertex *head){
	ListVertex *aux = head;
	printf("\n------List Vertex-------\n");
	while (aux != NULL){
		printf("(%d),", aux->v->value);
		aux= aux->next;
	}
	printf("\n-------------\n");
	
}

//Funções Lista Edges
ListEdge *insertEdge (Graph *graph, int vertex_origem, int vertex_destino){
  

  // Caso fosse usar a estrutura anterior e criar novos vertices (coloque isso no newElement)
    // Lembre-se também de mudar a estrutura de Edge e retirar o ponteiro
  
  // Cria vertices apontantes
  // Vertex vertexOrigem, vertexDestino;
  // vertexOrigem.value = vertex_origem;
  // vertexDestino.value = vertex_origem;


	ListEdge *aux,*newElement = malloc (sizeof(ListEdge));
	newElement->e = malloc (sizeof(Edge));
  newElement->e->origem = findVertex(graph->V, vertex_origem);
  newElement->e->destino = findVertex(graph->V, vertex_destino);

	if (graph->E == NULL){
		graph->E = newElement;
	}else{
		aux = graph->E;
		while ( aux->next != NULL){ 
			aux=aux->next;
		}
		aux->next = newElement;
		newElement->next = NULL;		
	}

	return graph->E;
}

void printListEdge(ListEdge *head){
	ListEdge *aux = head;
	printf("\n------List Edge-------\n");
	while (aux != NULL){
		printf("(%d, %d),", aux->e->origem->value, aux->e->destino->value);
		aux= aux->next;
	}
	printf("\n-------------\n");
	
}


//Pegar informações
void getInfoFromRegularGraph(Graph *graph){
  ListVertex *aux_list_vertex;
  ListEdge *aux_list_edge;
  int count;

  aux_list_vertex = graph->V;
  while (aux_list_vertex != NULL){
    count = 0;

    aux_list_edge = graph->E;
    while (aux_list_edge != NULL){
      if (aux_list_vertex->v->value == aux_list_edge->e->origem->value)
        count ++;
      if (aux_list_vertex->v->value == aux_list_edge->e->destino->value)
        count ++;

      aux_list_edge = aux_list_edge->next;    
    }

    printf("V(%d) = %d\n", aux_list_vertex->v->value, count);
    aux_list_vertex = aux_list_vertex->next;
  }
  
}

void getInfoFromOrientedGraph(Graph *graph){
  ListVertex *aux_list_vertex;
  ListEdge *aux_list_edge;
  int count;

  printf("\n------Saidas-------\n");
  aux_list_vertex = graph->V;
  while (aux_list_vertex != NULL){
    count = 0;

    aux_list_edge = graph->E;
    while (aux_list_edge != NULL){
      if (aux_list_vertex->v->value == aux_list_edge->e->origem->value)
        count ++;

      aux_list_edge = aux_list_edge->next;    
    }
    printf("V(%d) = %d\n", aux_list_vertex->v->value, count);
    aux_list_vertex = aux_list_vertex->next;
  }
  printf("\n-------------------\n");


  printf("\n------Entradas-------\n");
  aux_list_vertex = graph->V;
  while (aux_list_vertex != NULL){
    count = 0;

    aux_list_edge = graph->E;
    while (aux_list_edge != NULL){
      if (aux_list_vertex->v->value == aux_list_edge->e->destino->value)
        count ++;

      aux_list_edge = aux_list_edge->next;    
    }
    printf("V(%d) = %d\n", aux_list_vertex->v->value, count);
    aux_list_vertex = aux_list_vertex->next;
  }
  printf("\n-------------------\n");

  printf("\n------Sumidouro-------\n");
  aux_list_vertex = graph->V;
  while (aux_list_vertex != NULL){
    count = 0;

    aux_list_edge = graph->E;
    while (aux_list_edge != NULL){
      if (aux_list_vertex->v->value == aux_list_edge->e->origem->value)
        count ++;

      aux_list_edge = aux_list_edge->next;    
    }
    if (count == 0){
      printf("V(%d)\n", aux_list_vertex->v->value);
    }
    aux_list_vertex = aux_list_vertex->next;
  }
  printf("\n-------------------\n");

  printf("\n------Fonte-------\n");
  aux_list_vertex = graph->V;
  while (aux_list_vertex != NULL){
    count = 0;

    aux_list_edge = graph->E;
    while (aux_list_edge != NULL){
      if (aux_list_vertex->v->value == aux_list_edge->e->destino->value)
        count ++;

      aux_list_edge = aux_list_edge->next;    
    }
    if (count == 0){
      printf("V(%d)\n", aux_list_vertex->v->value);
    }
    aux_list_vertex = aux_list_vertex->next;
  }
  printf("\n-------------------\n");
  
}

/**
 * O que fazer:
 * 	1 - Fazer métodos inserção e print da lista de Edges
 *  2 - Ler um inteiro para saber se o grafo é orientado ou não.
 * 		- Se o grafo for regular:
 * 			-> Calcular o grau de todos os vértices;
 * 		- Se o grafo for orientado (dirigido):
 * 			-> Calcular o grau de entrada de todos os nodos;
 * 			-> Calcular o grau de saída de todos os nodos;
 * 			-> Listar os nodos que são fonte, eo nodos de sumidouro se existirem.
 * 
 */
int main(){
	Graph *graph = graphInit();
  int vertice_origem, vertice_destino, op=0;

  while (op != 6)
  {
    // Imprime opções
    printf("Digite a opção desejada \n\n");

    printf("1 Inserir vertice \n");
    printf("2 Inserir aresta \n");
    printf("3 Imprimir lista de vertice \n");
    printf("4 Imprimir lista de aresta \n");
    printf("5 Imprimir informações de grafo regular ou dirigido \n");
    printf("6 Finalizar\n");

    // Lê opção desejada
    scanf("%d%*c", &op);
    printf("\n");

    switch(op)
    {
      case 1 :
        printf("Informe o vertice\n");
        scanf("%d", &vertice_origem);
        graph->V = insertVertex(graph->V, vertice_origem);
        break;

      case 2 :
        printf("Informe os vertices da aresta:\n Origem Destino\n");
        scanf("%d %d", &vertice_origem, &vertice_destino);
        graph->E = insertEdge (graph, vertice_origem, vertice_destino);
        break;

      case 3 :
        printListVertex(graph->V);
        break;

      case 4 :
        printListEdge(graph->E);
        break;

      case 5 :
        // printListEdge(graph->E);
        // getInfoFromRegularGraph(graph);
        getInfoFromOrientedGraph(graph);
        break;
    }
  }

	return 0;
}
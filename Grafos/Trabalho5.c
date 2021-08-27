#include <stdio.h>
#include <stdlib.h>

// Configurações do programa
#define GRAPH_SIZE 8
#define DEFAULT_INFINITE 1000
#define DEFAULT_PREVIOUS -1000

// Structs
struct data
{ //Armazena dados do grafo
  
  int distance[GRAPH_SIZE];
  int previous[GRAPH_SIZE];
  char color[GRAPH_SIZE];
};
typedef struct data Data;

struct pile_or_row
{ //Estrutura para pilhas ou filas
  
  int value;
  struct pile_or_row *next;
};
typedef struct pile_or_row PileOrRow;

struct row
{ // Estrutura para armazenar elementos da fila

  PileOrRow *first;
  PileOrRow *last;
};
typedef struct row Row;

struct pile
{ // Estrutura para armazenar elementos da pilha
  
  PileOrRow *top;
};
typedef struct pile Pile;

// Functions
// ----- Dados -----
Data *initData( int initialVertex ) {

  // Inicia valores
  Data *data = malloc (sizeof(Data));
  int currentVertex;

  for ( currentVertex = 0; currentVertex < GRAPH_SIZE; currentVertex++ )
  { // Percorre dados para iniciar valores
    
    if ( currentVertex == initialVertex )
    { // Caso vertice ser o vertice inicial
      
      data->distance[currentVertex] = 0;
      data->previous[currentVertex] = -1;
      data->color[currentVertex] = 'g';
    } else
    {
      data->distance[currentVertex] = DEFAULT_INFINITE;
      data->previous[currentVertex] = DEFAULT_PREVIOUS;
      data->color[currentVertex] = 'w';
    }

  }
  
	return data;
}

void printData( Data *data ) {

  // Inicia variaveis
  int curVer;

  printf("Vert.\t| Dist.\t| Prev.\t| Color\n");
  for ( curVer = 0; curVer < GRAPH_SIZE; curVer++ )
  { // Percorre dados imprimindo-os
    
    printf( "%d\t| %d\t| %d\t| %c\n", curVer, data->distance[curVer], data->previous[curVer], data->color[curVer]);
  }
  printf("\n");
}
// ----- Dados -----

// ----- Pilha -----
Pile *initPile() {
  Pile *pile  = malloc (sizeof(Pile));
  pile->top = NULL;

  return pile;
}

void insertInPile(Pile *pile, int item) {
  
  // Inicia elemento
  PileOrRow *auxPile = malloc(sizeof(PileOrRow));
  
  // Armazena elemento
  auxPile->value = item;
  auxPile->next = pile->top;
  pile->top = auxPile;
}

void removeFromPile(Pile *pile) {
  
  // Inicia elemento
  PileOrRow *auxPile;

  // Remove elemento
  auxPile = pile->top;
  pile->top = pile->top->next;

  // Libera elemento
  free(auxPile);
}

void printPile(Pile *pile) {
  PileOrRow *pile_or_row = pile->top;
  
  printf("Pilha: ");
  while ( pile_or_row != NULL)
  {
    printf("%d, ", pile_or_row->value);
    pile_or_row = pile_or_row->next;
  }
  printf("\n");
  
}

void analyzeDfs( Pile *pile, Data *data, int graph[GRAPH_SIZE][GRAPH_SIZE] ) 
{
  // Inicializa variaveis
  int curAdj, curVer = pile->top->value;

  for ( curAdj = 0; curAdj < GRAPH_SIZE; curAdj++ )
  { // Percorre matriz
    
    if ( graph[curVer][curAdj] != 0 && data->color[curAdj] == 'w' )
    { // Verefica se há uma curAdj no curVer, e se a cor é branco

      // Insere elemento na pilha
      insertInPile(pile, curAdj);

      // Salva dados desse elemento
      data->distance[curAdj] = (data->distance[curVer] + 1);
      data->previous[curAdj] = curVer;
      data->color[curAdj] = 'g';

      // Chama função com o novo topo
      analyzeDfs(pile, data, graph);
    }
  }

  // Imprime dados
  printf("Vertice atual: %d \n", curVer);
  printPile(pile);
  printData(data);

  // Atualiza dados
  data->color[curVer] = 'b';
  removeFromPile(pile);
}
// ----- Pilha -----

// ----- Fila -----
Row *initRow() {
  Row *row = malloc (sizeof(Row));
  row->first = NULL;
  row->last = NULL;

  return row;
}

void insertInRow(Row *row, int item) {

  // Inicia elemento
  PileOrRow *auxRow = malloc(sizeof(PileOrRow));
  auxRow->value = item;
  auxRow->next = NULL;

  if ( row->first == NULL )
  { // Caso a pilha estiver vazia
    
    row->first = auxRow;
    row->last = auxRow;
  } else
  {
    row->last->next = auxRow;
    row->last = auxRow;
  }
}

void removeFromRow(Row *row) {
  
  // Inicia valores
  PileOrRow *auxRow = row->first;

  if (row->first == row->last)
  { // Caso tiver apenas um elemento
    
    row->first = NULL;
    row->last = NULL;
  } else
  {
    row->first = row->first->next;
  }

  // Libera elemento
  free(auxRow);
}

void printRow(Row *row) {
  PileOrRow *pile_or_row = row->first;
  
  printf("Lista: ");
  while ( pile_or_row != NULL)
  {
    printf("%d, ", pile_or_row->value);
    pile_or_row = pile_or_row->next;
  }
  printf("\n");
  
}

void analyzeBfs( Row *row, Data *data, int graph[GRAPH_SIZE][GRAPH_SIZE] ) 
{

  while (row->first != NULL)
  {

    // Inicializa variaveis
    int curAdj, curVer = row->first->value;
    
    // Imprime vertice atual
    printf("Vertice atual: %d \n", curVer);

    for ( curAdj = 0; curAdj < GRAPH_SIZE; curAdj++ )
    { // Percorre matriz

      if ( graph[curVer][curAdj] != 0 && data->color[curAdj] == 'w' )
      { // Verefica se há uma curAdj no curVer, e se a cor é branco

        // Insere elemento na fila
        insertInRow(row, curAdj);

        // Salva dados desse elemento
        data->distance[curAdj] = (data->distance[curVer] + 1);
        data->previous[curAdj] = curVer;
        data->color[curAdj] = 'g';
      }

    }
    // Imprime valores a cada condição
    printRow(row);
    printData(data);

    // Atualiza dados
    data->color[curVer] = 'b';
    removeFromRow(row);

  }
}
// ----- Fila -----

int main(){

  int graph[GRAPH_SIZE][GRAPH_SIZE] = {
    { 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 1, 0, 1, 1, 0 },
    { 1, 1, 0, 0, 0, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 1, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 1, 0, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0 },
  };

  // Usado para definir tipo que será usado
  int type;
  printf("Informe o tipo desejado: \n\t1) BFS\n\t2) DFS\n\t :");
  scanf("%d", &type);

  int initialValue;
  printf("Informe o valor inicial: ");
  scanf("%d", &initialValue);


  Data *data = initData(initialValue);

  if (type == 1)
  { // Caso o tipo ser BFS 

    Row *row = initRow();
    insertInRow(row, initialValue);
    analyzeBfs(row, data, graph);

    // Imprime valores finais
    printf("Versão final\n");
    printData(data);
  } else if (type == 2)
  { // Caso o tipo ser DFS

    Pile *pile = initPile();
    insertInPile(pile, initialValue);
    analyzeDfs(pile, data, graph);

    // Imprime valores finais
    printf("Versão final\n");
    printData(data);
  } else
  {
    printf("Tipo informado inválido\n");
  }

  return 0;
}
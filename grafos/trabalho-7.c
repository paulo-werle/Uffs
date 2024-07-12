#include <stdio.h>
#include <stdlib.h>

// Define valores
#define SIZE 8

#define COLOR_RED    "\033[0;31m"
#define COLOR_GREEN  "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE   "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN   "\033[0;36m"
#define COLOR_WHITE  "\033[0;37m"
#define COLOR_RESET  "\x1b[0m"

// Metodo para mudar print de cor
void printColor(int color){
  
  switch (color){
    case 1:
      printf(COLOR_RED "1\n" COLOR_RESET);
      break;

    case 2:
      printf(COLOR_GREEN "2\n" COLOR_RESET);
      break;

    case 3:
      printf(COLOR_BLUE "3\n" COLOR_RESET);
      break;

    case 4:
      printf(COLOR_PURPLE "4\n" COLOR_RESET);
      break;

    case 5:
      printf(COLOR_CYAN "5\n" COLOR_RESET);
      break;

    default:
      printf("default\n");
  }
}
// Metodo para mudar print de cor

void initColors( int color[SIZE] ){
  int i;

  for( i = 0; i < SIZE; i++){
    color[i] = 0;
  }
}

int getTotalColor(int color[SIZE]){
  // Iniciando variaveis
  int i, totalColor = 0;

  // Percorre array com cores
  for ( i = 0; i < SIZE; i++){
    
    // Caso numero da cor seja maior que o totalColor
    if (color[i] > totalColor){
      totalColor = color[i]; 
    }
  }

  return totalColor;
}

void printColors( int color[SIZE] ){
  int i;

  printf("DADOS DAS CORES: \n");
  for( i = 0; i < SIZE; i++){
    printf("%d): ", i);
    printColor(color[i]);
  }

  printf("\nFoi utilizado %d cor(es) para pintar o grafo\n", getTotalColor(color) );
}

void colorGraph( int graph[SIZE][SIZE], int color[SIZE] ){
  // Inicia variaveis
  int currentColor, currentAdjacentEdge, currentEdge = 0;

  // Percorre os vertices do grafo
  while( currentEdge < SIZE ){
    
    // Define dados iniciais
    currentColor = 1;
    currentAdjacentEdge = 0;

    // Coloca cor inicial
    color[currentEdge] = currentColor;
    
    // Percorre as adjacencias do vertice
    while( currentAdjacentEdge < SIZE){

      // Caso o grafo possuir uma arresta para outro vertice 
      if ( graph[currentEdge][currentAdjacentEdge] ){
        
        // Caso o vertice adjacente já tiver cor, e a cor for a mesma que a atual
        if ( color[currentAdjacentEdge] && color[currentAdjacentEdge] == color[currentEdge] ){
          
          // Coloca nova cor 
          color[currentEdge] = ++currentColor;

          // Redefine current, para testar se outro vertice já testado não possui a cor atual
          currentAdjacentEdge = 0;
        }
      }
      currentAdjacentEdge++;
    }
    currentEdge++;
  }
}

// Principal
int main(){
  int color[SIZE];

  int graph[SIZE][SIZE] = {
    { 0, 4, 3, 8, 0, 0, 0, 0 },
    { 4, 0, 8, 0, 0, 0, 7, 0 },
    { 3, 8, 0, 0, 0, 0, 9, 0 },
    { 8, 0, 0, 0, 0, 9, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 4 },
    { 0, 0, 0, 9, 0, 0, 0, 2 },
    { 0, 7, 9, 0, 0, 0, 0, 4 },
    { 0, 0, 0, 0, 4, 2, 4, 0 },
  };

  // Inicia cores no array
  initColors(color);

  // Colore grafo
  colorGraph(graph, color);

  // Imprime cores do grafo
  printColors(color);
  
	return 0;
}
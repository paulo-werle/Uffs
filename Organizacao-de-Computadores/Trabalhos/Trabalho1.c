#include <stdio.h>

#define BOARD_SIZE 10

// novoTabuleiro( int board[BOARD_SIZE][BOARD_SIZE])
void newBoard( int board[BOARD_SIZE][BOARD_SIZE] ) {
  int boardRow, boardCol;

  for ( boardRow = 0; boardRow < BOARD_SIZE; boardRow++)
    for ( boardCol = 0; boardCol < BOARD_SIZE; boardCol++)
      board[boardRow][boardCol] = 0; // Coloca valor inicial
}

// InserirTabuleiro( int board[BOARD_SIZE][BOARD_SIZE], int angle, int length, int row, int col, int current )
void insertBoard( int board[BOARD_SIZE][BOARD_SIZE], int angle, int length, int row, int col, int current ) {
  int insertions;
  
  for ( insertions = 0; insertions < length; insertions++) {
    if (angle) // Vertical
      board[row + insertions][col] = current;  
    
    else // Horizontal
      board[row][col + insertions] = current;

  }
}

// imprimeBarcos( int board[BOARD_SIZE][BOARD_SIZE])
void printBoard( int board[BOARD_SIZE][BOARD_SIZE]) {
  int boardRow, boardCol;
  
  for ( boardRow = 0; boardRow < BOARD_SIZE; boardRow++)
  {
    for ( boardCol = 0; boardCol < BOARD_SIZE; boardCol++)
    {
      printf(" %d ", board[boardRow][boardCol]);
    }
    printf("\n");
  }
}


// validaInsercoes( int board[BOARD_SIZE][BOARD_SIZE], int angle, int length, int row, int col ) return int
int validateInserts( int board[BOARD_SIZE][BOARD_SIZE], int angle, int length, int row, int col ) {
  int insertions;

  if (row > BOARD_SIZE || col > BOARD_SIZE)
    return 1; // A posição do navio é inválida


  if (angle){ // Vertical
    if ( (row + length) > BOARD_SIZE )
      return 2; // O navio extrapola as dimensões da matriz.

  } else { // Horizontal
    if ( (col + length) > BOARD_SIZE )
      return 2; // O navio extrapola as dimensões da matriz.
  } 


  for ( insertions = 0; insertions < length; insertions++) {
    if (angle){ // Vertical
      if ( board[row + insertions][col])
        return 3; // Ocorre sobreposição nos navios.
    
    } else { // Horizontal
      if ( board[row][col + insertions])
        return 3; // Ocorre sobreposição nos navios.
    }
  }

  return 0; // Não possui erros
}

// insereEmbarcacoes( int board[BOARD_SIZE][BOARD_SIZE] )
void boatInsertion( int board[BOARD_SIZE][BOARD_SIZE] ) {
  // Variaveis auxiliares
  int current, quantity, error, insertions;

  // Parametros a ser utilizados
  int angle, length, row, col;
  
  printf("Informe a quantidade de embarações: ");
  scanf("%d", &quantity);

  for ( current = 1; current <= quantity; current++ )
  {
    printf("Informe os dados do %d° barco: ", current);
    scanf("%d %d %d %d", &angle, &length, &row, &col);

    // Faz validação dos dados
    error = validateInserts( board, angle, length, row, col );

    if ( !error)
    { // Não possui erros

      insertBoard(board, angle, length, row, col, current );
      printBoard(board);

    } else
    { // Avisa que há erros
      printf("O erro é :%d\n", error);
      break;
    }
  }
}

int main() {
  // Inicializa variavel para Tabuleiro
  int board[BOARD_SIZE][BOARD_SIZE];
  
  // Inicia tabuleiro
  newBoard(board);

  // Insere barcos
  boatInsertion(board);
    

  return 0;
}
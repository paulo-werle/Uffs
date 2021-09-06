#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define NAVIOS "3\n1 5 1 1\n0 5 2 2\n0 1 6 4\n"

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
  printf("\n");
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

int parseInt(int *error, char current, char next) {
  if ( !*error )
  { // Caso não tenha erro valida dado
    
    if (next == ' ' || next == '\n')
      return current - '0';

    // Atualiza erro
      *error = 4;
  }

  // Retorna 0 pois houve um erro
  return 0;
}

// insereEmbarcacoes( int board[BOARD_SIZE][BOARD_SIZE] )
void boatInsertion( int board[BOARD_SIZE][BOARD_SIZE] ) {
  // Variaveis auxiliares
  int current, quantity, insertions, count, error = 0;

  // Parametros a ser utilizados
  int angle, length, row, col;

  // Define string de navios
  char navios[] = NAVIOS;

  // Define quantity
  quantity = parseInt(&error, navios[0], navios[1]);

  if ( !error )
  { // Caso não tiver erros

    for ( current = 1; current <= quantity; current++ )
    {

      count = ( (current - 1) * 8) + 2;
      angle = parseInt(&error, navios[ count ], navios[count + 1]);

      count = count + 2;
      length = parseInt(&error, navios[ count ], navios[count + 1]);

      count = count + 2;
      row = parseInt(&error, navios[ count ], navios[count + 1]);

      count = count + 2;
      col = parseInt(&error, navios[ count ], navios[count + 1]);
    
      if ( !error )
      { // Não possui erros

        // Faz validação dos dados
        error = validateInserts( board, angle, length, row, col );
      }

      if ( !error )
      { // Não possui erros

        insertBoard(board, angle, length, row, col, current );
        printBoard(board);

      } else
      { // Avisa que há erros
        printf("O erro é :%d\n", error);
        break;
      }
    }
  } else {
    printf("O erro é :%d\n", error);
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
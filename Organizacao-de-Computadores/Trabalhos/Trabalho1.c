#include <stdio.h>
#include <stdlib.h>

#define BOARD_SIZE 10
#define NAVIOS "3\n1 1 1 1\n0 1 2 2\n0 1 6 4\n"

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
void printShips( int board[BOARD_SIZE][BOARD_SIZE]) {
  int boardRow, boardCol;

  for ( boardRow = 0; boardRow < BOARD_SIZE; boardRow++)
  {
    for ( boardCol = 0; boardCol < BOARD_SIZE; boardCol++)
    {
      printf("%d\t", board[boardRow][boardCol]);
    }
    printf("\n");
  }
  printf("\n");
}

// imprimeTiros( int board[BOARD_SIZE][BOARD_SIZE])
void printShots( int board[BOARD_SIZE][BOARD_SIZE]) {
  int boardRow, boardCol;

  for ( boardRow = 0; boardRow < BOARD_SIZE; boardRow++)
  {
    for ( boardCol = 0; boardCol < BOARD_SIZE; boardCol++)
    {

      if ( board[boardRow][boardCol] == -1 )
      { // É um tiro na agua
        printf(" ø ");

      } else if ( board[boardRow][boardCol] >= 0 && board[boardRow][boardCol] <= 10)
      { // É agua ou navio que não foi atirado
        printf(" o ");

      } else
      { // É um tiro em um navio
        printf(" x ");

      }

    }
    printf("\n");
  }
  printf("\n\n");
}

// imprimeDados( int shots_record, int hits_record, int sunk_record, int shots, int hits, int sunk )
void printData( int shots_record, int hits_record, int sunk_record, int shots, int hits, int sunk ){
  printf("Record: --------\n");
  printf("- Tiros: %d \n", shots_record);
  printf("- Acertos: %d \n", hits_record);
  printf("- Afundados: %d \n", sunk_record);
  printf("----------------\n");

  printf("Voce: ----------\n");
  printf("- Tiros: %d \n", shots);
  printf("- Acertos: %d \n", hits);
  printf("- Afundados: %d \n", sunk);
  printf("----------------\n");
}

// confereBarcos( int board[BOARD_SIZE][BOARD_SIZE], int ships )
int checkShips( int board[BOARD_SIZE][BOARD_SIZE], int ships, int *sunk ) {
  
  // Inica variaveis
  int boardRow, boardCol, quantity = 0;

  for( boardRow = 0; boardRow < BOARD_SIZE; boardRow++)
  {
    for( boardCol = 0; boardCol < BOARD_SIZE; boardCol++)
    {
    
      if ( ships )
      { // Confere peças do barco
        
        // Confere quantidade de peças do barco ainda estão presentes 
        if ( board[boardRow][boardCol] == ships )
          quantity += 1;

      } else
      { //Confere se ainda tem barcos

        // Confere quantidade de peças ainda presente
        if ( board[boardRow][boardCol] >= 1 && board[boardRow][boardCol] <= 10 )
          quantity += 1;
        
      }
    }
  }

  if ( !quantity && ships )
  { // Caso não tenha mais navios no tabuleiro
    printf("O navio %d foi totalmente destruido\n", ships);
    *sunk += 1;
  }

  // Retorna quantidade
  return quantity;
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

// converterInteiro(int *error, char current, char next)
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
void boatInsertion( int board[BOARD_SIZE][BOARD_SIZE], int *error, int *quantity_ships ) {
  // Variaveis auxiliares
  int current, quantity, insertions, count;
  // Parametros a ser utilizados
  int angle, length, row, col;

  // Define a quantidade até o momento
  *error = 0;
  *quantity_ships = 0;

  // Define string de navios
  char navios[] = NAVIOS;

  // Define quantity
  quantity = parseInt(error, navios[0], navios[1]);

  if ( !*error )
  { // Caso não tiver erros

    for ( current = 1; current <= quantity; current++ )
    {

      count = ( (current - 1) * 8) + 2;
      angle = parseInt(error, navios[ count ], navios[count + 1]);

      count = count + 2;
      length = parseInt(error, navios[ count ], navios[count + 1]);

      count = count + 2;
      row = parseInt(error, navios[ count ], navios[count + 1]);

      count = count + 2;
      col = parseInt(error, navios[ count ], navios[count + 1]);

      if ( !*error )
      { // Não possui erros

        // Faz validação dos dados
        *error = validateInserts( board, angle, length, row, col );
      }

      if ( !*error )
      { // Não possui erros

        insertBoard(board, angle, length, row, col, current );
        *quantity_ships += 1;
        // printShips(board);

      } else
      { // Avisa que há erros
        printf("O erro é :%d\n", *error);
        break;
      }
    }
  } else {
    printf("O erro é :%d\n", *error);
  }
}

// novaJogada( int board[BOARD_SIZE][BOARD_SIZE] )
void newMove( int board[BOARD_SIZE][BOARD_SIZE], int *shots, int *hits, int *sunk ){

  // Inicia variaveis
  int ship = 0, row, col;

  // Coleta dados
  printf("Informe: Linha,Coluna:\n");
  scanf("%d,%d", &row, &col);

  if ( board[row][col] >= 0 && board[row][col] <= 10)
  { // Verefica se a jogada já não foi realizada

    if ( board[row][col] )
    { // Indica que o tiro foi em um navio

      // Aguarda numero do navio e atualiza dado
      ship = board[row][col];
      board[row][col] += 10;
      *hits += 1;
      
    } else
    { // Indica que o tiro foi na agua

      board[row][col] = -1;
    }
  } else
  { // Caso jogada já tenha sido feita

    printf("Esta jogada já foi feita anteriormente \n");
  }

  // Imprime dados de tiros
  printShots(board);
  
  // Verefica se um navio foi destruido
  *shots += 1;
  checkShips(board, ship, sunk);
}

// menu()
int menu() {
  // Inicia variavel
  int op;

  // Imprime opções
  printf("\n");
  printf("Informe qual ação deseja fazer: \n");
  printf("0: Sair do jogo \n");
  printf("1: Fazer uma nova jogada \n");
  printf("2: Mostrar navios \n");
  printf("3: Reiniciar jogo \n");
  scanf("%d", &op );
  printf("\n\n");

  return op;
}


int main() {
  int error, quantity_ships, operation = 3;
  int shots_record = 100, hits_record = 0, sunk_record = 0, shots = 0, hits = 0, sunk = 0;
  int aux = 0;

  // Inicializa variavel para Tabuleiro
  int board[BOARD_SIZE][BOARD_SIZE];

  // Inicia tabuleiro
  newBoard(board);

  // Insere barcos
  boatInsertion(board, &error, &quantity_ships);

  while ( operation && quantity_ships && !error ) {
    operation = menu();

    switch ( operation )
    {
      case 1: //  Fazer nova jogada
        newMove(board, &shots, &hits, &sunk );
        printData(shots_record, hits_record, sunk_record, shots, hits, sunk);
        break;

      case 2: //  Mostrar navios
        printShips(board);
        break;

      case 3: // Reiniciar jogo
        newBoard(board);
        boatInsertion(board, &error, &quantity_ships);
        shots = 0;
        hits = 0;
        sunk = 0;
        break;
    }

    // Verefica quantidade de peças para saber se é vencedor
    quantity_ships = checkShips(board, 0, &aux);
    if ( !quantity_ships ){
      
      // Imprime mensagem do vencedor
      printf("Temos um VENCEDOR\n");

      // Caso ser um novo record
      if ( shots < shots_record)
      {
        shots_record = shots;
        hits_record = hits;
        sunk_record = sunk;
      }

      // Redefine parametros para iniciar um novo jogo
      newBoard(board);
      boatInsertion(board, &error, &quantity_ships);
      shots = 0;
      hits = 0;
      sunk = 0;
    }
  }

  return 0;
}
// Como utilizar:
// gcc Trabalho4.c -lpthread -lm -o nome_do_arquivo
// ./ nome_do_arquivo numero_de_threads numero_de_interacoes

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#define TAMANHO_DO_VETOR 10000

pthread_barrier_t barrier;
int numBarriers;

// TODO - Colocado as variaveis abaixo como variaveis globais para não precisar
// criar struct para os argumentos da função da thread, porem acredito que não é uma
// boa pratica
int numThreads, numIterations;
float oldVector[TAMANHO_DO_VETOR] = {0}, newVector[TAMANHO_DO_VETOR] = {0};

void validateUsage(
  int argc, char *argv[]
);
void *threadFunction(
  void *arg
);
void calcNewVector(
  int start, int end
);
void calculateStartAndEnd(
  long threadId, int *start, int *end
);
void printVector(
  char vector_name[], float vector[]
);
void swapVectors();

int main( int argc, char *argv[] ) {
  pthread_t *threads;

  // Valida forma de uso
  validateUsage( argc, argv );

  // Transforma parametros em int
  numThreads    = atoi( argv[1] );
  numIterations = atoi( argv[2] );

  // Define valor 1 na borda dos vetores
  newVector[TAMANHO_DO_VETOR - 1] = 1;
  oldVector[TAMANHO_DO_VETOR - 1] = 1;

  // Alocação das threads
  threads = calloc( sizeof(pthread_t), numThreads);
  if ( threads == NULL ) {
    printf("Erro ao alocar threads \n");
  }

  // Inicia barreira
  if ( pthread_barrier_init(&barrier, NULL, numThreads) ) {
    printf("Erro ao iniciar barreira \n");
  }

  // Cria o numero de threads passado por argumento
  for ( long count = 0; count < numThreads; count++ ) {
    if ( pthread_create(&threads[count], NULL, &threadFunction, (void *) count) ) {
      printf("Erro ao criar thread \n");
    }
  }

  // Junta o numero de threads passado por argumento
  for ( int count = 0; count < numThreads; count++ ) {
    if ( pthread_join(threads[count], NULL) ){
      printf("Erro ao juntar thread");
    }
  }

  exit(0);
}

// Faz a validação se os argumentos estão corretos na hora de executar o programa
void validateUsage( int argc, char *argv[] ) {
  if ( argc != 3 || strcmp(argv[1], "--help" ) == 0) {
    printf("Usage: %s num-threads num-iterations \n", argv[0]);
  }
}

// Monta função para cada thread
void *threadFunction(void *arg) {

  // Argumento da função
  long threadId = (long) arg;

  // Inicia variaveis e calcula tamanho da fatia
  int pthread_barrier, start, end;
  calculateStartAndEnd(threadId, &start, &end);

  for ( int count = 1; count < numIterations; count++ ) {

    // Aguarda todos chegarem aqui e calcula convergencia do novo vetor
    pthread_barrier = pthread_barrier_wait(&barrier);
    calcNewVector(start, end);

    // Aguarda todos chegarem aqui e uma das threads faz o swap entre os vetores (swap do vetor inteiro)
    if ( pthread_barrier_wait(&barrier) == PTHREAD_BARRIER_SERIAL_THREAD ) {
      swapVectors();
    };

  }

  printVector("oldVector", oldVector);
}

// Realiza calculo para saber as fatias de cada thread
void calculateStartAndEnd( long threadId, int *start, int *end ) {
  double size = TAMANHO_DO_VETOR - 2;
  int slice = ceil( size / numThreads);

  *start = threadId * slice + 1;
  *end = *start + slice - 1;
  if ( *end > (TAMANHO_DO_VETOR - 2) ) {
    *end = TAMANHO_DO_VETOR - 2;
  }
}

// Realiza a operação Novo[i] = (Velho[i - 1] + Velho[i + 1]) / 2
void calcNewVector( int start, int end ) {
  for ( int count = start; count <= end; count++ ) {
    newVector[count] = (oldVector[count - 1] + oldVector[count + 1]) / 2;
  }
}

// Realiza swap entre os vetores (vetor inteiro)
void swapVectors() {
  float tmp;

  for ( int count = 0; count < TAMANHO_DO_VETOR; count++ ) {
    tmp = newVector[count];
    newVector[count] = oldVector[count];
    oldVector[count] = tmp;
  }
}

// Imprime valores do vetor
void printVector( char vector_name[], float vector[] ) {
  for ( int count = 0; count < TAMANHO_DO_VETOR; count++ ) {
    printf("%s[%d]: %.5f \t", vector_name, count, vector[count]);
  }
}
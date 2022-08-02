#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dataStructure.c"
#include "importers.h"

// Informações do roteador
Information *information;

// Threads
pthread_t terminalTh;

// Listas
List *entryList;
List *exitList;

void callThreads() {
  pthread_create(&terminalTh, NULL, &terminalFn, NULL);
}

void unmountThreads() {
  pthread_join(terminalTh, NULL);
}

int main(int number, char *args[]) {

  // Define informações sobre o roteador
  int id = executionArguments(number, args);
  setInformation(id);

  // Manipula threads
  callThreads();
  unmountThreads();

  // output

  return 0;
}
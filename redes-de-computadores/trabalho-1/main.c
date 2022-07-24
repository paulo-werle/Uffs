#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "includes.h"
#include "dataStructure.c"

// Informações do roteador
Information *information;

int main(int number, char *args[]) {

  int id = executionArguments(number, args);
  setInformation(id);

  return 0;
}
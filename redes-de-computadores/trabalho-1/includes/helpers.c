#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../includes.h"
#include "../dataStructure.c"

// Arquivos de funções para ajuda
void reportError(char *message) {
  perror(message);
  exit(1);
}

int executionArguments(int number, char *args[]) {
  if (number != 2 || !strcmp(args[1], "--help")) {
    printf("Usage: %s <router_id> \n", args[0]);
    exit(1);
  }

  return atoi(args[1]);
}
#include "../dataStructure.c"
#include "../importers.h"

void *packetHandlerFn() {
  while(true) {
    sem_wait(&packetHandlerSm);
  }
}
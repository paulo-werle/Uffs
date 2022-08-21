#include "../dataStructure.c"
#include "../importers.h"

List *insertInTheList(List *list, Structure *structure) {
  List *auxE, *newE = malloc(sizeof(List));

  newE->structure = structure;
  newE->next = NULL;

  if (list == NULL) {
    list = newE;

  } else {
    auxE = list;

    while (auxE->next != NULL)
      auxE = auxE->next;

    auxE->next = newE;
  }

  return list;
}

List *removeFromList(List *list) {
  List *auxE = list->next;

  free(list);
  return auxE;
}
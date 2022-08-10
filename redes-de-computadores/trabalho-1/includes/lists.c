#include "../dataStructure.c"
#include "../importers.h"

List *insertInTheList(List *list, MessageStructure *msg) {
  List *auxE, *newE = malloc( sizeof(List) );

  newE->messageStructure = msg;

  if (list == NULL) {
    list = newE;

  } else {
    auxE = list;

    while (auxE->next != NULL)
      auxE = auxE->next;

    auxE->next = newE;
    newE->next = NULL;
  }

  return list;
}

List *removeFromList(List *list) {
  List *auxE = list->next;

  free(list);
  return auxE;
}
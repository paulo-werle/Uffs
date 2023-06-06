#include "../importers.h"

// Função: insertOrderedInTheList
//   description: Responsavel por inserir itens na lista ordenadamente
//   params: list<List>, structure<Structure>
//   return: list<List>
List *insertOrderedInTheList(List *list, Structure *structure) {
  List *auxE, *newE = malloc(sizeof(List));

  newE->structure = structure;
  newE->next = NULL;

  if (list == NULL) {
    list = newE;

  } else if (newE->structure->relativeTime < list->structure->relativeTime) {
    newE->next = list;
    list = newE;

  } else {
    auxE = list;
    while (auxE->next != NULL && newE->structure->relativeTime > auxE->structure->relativeTime) {
      auxE = auxE->next;
    }
    newE->next = auxE->next;
    auxE->next = newE;
  }

  return list;
}

// Função: insertInTheList
//   description: Responsavel por inserir itens na lista
//   params: list<List>, structure<Structure>
//   return: list<List>
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

// Função: removeFromList
//   description: Responsavel por remover item da lista
//   params: list<List>
//   return: list<List>
List *removeFromList(List *list) {
  List *auxE = list->next;

  free(list);
  return auxE;
}
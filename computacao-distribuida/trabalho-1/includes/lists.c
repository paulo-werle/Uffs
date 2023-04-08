#include "../importers.h"

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
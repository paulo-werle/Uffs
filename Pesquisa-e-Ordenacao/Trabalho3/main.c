#include <stdio.h>
#include <string.h>
#include "radixSort.c"

int main(){

  // Cria produtos
  Product products[10] = { 
    {100, "Camiseta"}, 
    {300, "Calça"}, 
    {500, "Shorts"}, 
    {700, "Chinelo"},
    {900, "Casaco"},
    {150, "Tenis"}, 
    {800, "Saia"},
    {600, "Sapato"}, 
    {400, "Moletom"}, 
    {200, "Bermuda"}
  };

  // Chama ordenação
  radixSort(products, 10);

  // Imprime resultado
  printValues(products, 10);

  return 0;
}
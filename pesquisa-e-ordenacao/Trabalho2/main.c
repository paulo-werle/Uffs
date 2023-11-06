// Libs
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Sorts
#include "mergeSort.c"
#include "quickSort.c"
#include "heapSort.c"

int main(){

  // Cria variaveis
  clock_t time_start, time_end;
  int merge_sort[100000], quick_sort[100000], heap_sort[100000];
  int aux, count;
  
  // Prenche valores de entrada
  for (count=0; count<=99999; count++) {
    scanf(", %d", &aux);
    merge_sort[count]= aux;
    quick_sort[count]= aux; 
    heap_sort[count] = aux;
  }

  // Executa - MERGE SORT
  time_start = clock();
  mergeSort(merge_sort, 0, 99999);
  time_end = clock();
  double dif_time_merge_sort = ((double) time_end - time_start)/CLOCKS_PER_SEC;

  // Executa - QUICK SORT
  time_start = clock();
  quickSort(quick_sort, 0, 99999);
  time_end = clock();
  double dif_time_quick_sort = ((double) time_end - time_start)/CLOCKS_PER_SEC;

  // Executa - HEAP SORT
  time_start = clock();
  heapSort(heap_sort, 100000);
  time_end = clock();
  double dif_time_heap_sort = ((double) time_end - time_start)/CLOCKS_PER_SEC;


  printf("\n\t MERGE SORT: Tempo em segundos: %lf", dif_time_merge_sort);
  printf("\n\t QUICK SORT: Tempo em segundos: %lf", dif_time_quick_sort);
  printf("\n\t HEAP SORT: Tempo em segundos: %lf", dif_time_heap_sort);

  return 0;
}
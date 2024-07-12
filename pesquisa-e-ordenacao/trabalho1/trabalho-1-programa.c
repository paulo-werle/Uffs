#include <stdio.h>
#include <time.h>
// OBS: Para testar e obter os tempos de execução, foi comentado as linhas não necessarias, também foi usado os mesmos arquivos para todos os testes

// BUBBLE SORT
void bubble_sort (int array[], int n) {
  int count1, count2, aux, order;

  // Início
  //   para i de n-1 até 1 faça
  //     flag = falso
  //     para j de 0 até i-1 faça
  //       se A[j] > a[j+1] então
  //         troca(A[j], A[j+1])
  //         flag = verdadeiro
  //       fimSe
  //     fimPara
  //     se flag = falso então
  //       interrompa
  //     fimSe
  //   fimPara
  // fimAlgoritmo

  // Laço para percorrer todo array
  for (count1 = (n-1); count1>=1; count1--) {
    order = 0;

    // Laço para trocar elemento
    for (count2 = 0; count2 <= (count1-1); count2++) {  

      // Verefica para ordenar
      if (array[count2] > array[count2 + 1]) {

        // Faz a troca
        aux = array[count2];
        array[count2] = array[count2 + 1];
        array[count2 + 1] = aux;

        order = 1;
      }
    }
    if (order == 0) {
      break;
    }
  }
}

// SELECTION SORT
void selection_sort (int array[], int n) {
  int count1, count2, aux, menor;

  // Início
  //   para i de 0 até n-2 faça
  //     menor = i
  //     para j de i+1 até n-1 faça
  //       se A[menor] > A[j] então
  //         menor = j
  //       fimSe
  //     fimPara
  //     troca(A[i], A[menor])
  //   fimPara
  // fimAlgoritmo

  // Laço para percorrer todo array
  for (count1 = 0; count1<=(n-2); count1++) {
    menor = count1;

    // Laço para trocar elemento
    for (count2 = (count1+1); count2<=(n-1); count2++) {

      // Verefica para ordenar
      if (array[menor] > array[count2]) {
        menor = count2;
      }
    }

    // Faz a troca
    aux = array[count1];
    array[count1] = array[menor];
    array[menor] = aux;
  }
}

// INSERTION SORT
void insertion_sort (int array[], int n) {
  int count1, count2, aux, item;

  // Início
  //   para i de 1 até n-1 faça
  //     p = A[i]
  //     para j de i até 1 e p < A[j-1] faça
  //       A[j] = A[j-1]
  //     fimPara
  //     A[j] = p
  //   fimPara
  // fimAlgoritmo

  // Laço para percorrer todo array
  for (count1 = 1; count1<=(n-1); count1++) {
    item = array[count1];

    // Laço para trocar elemento
    for (count2 = count1; (count2 >= 1) && (item < array[count2-1]); count2--) { 
      array[count2] = array[count2-1];
    }
    array[count2] = item;
  }
}

int main(){
  // Cria tempos
  clock_t bubble_sort_start, bubble_sort_end;
  clock_t selection_sort_start, selection_sort_end;
  clock_t insertion_sort_start, insertion_sort_end;

  // Cria Arrays
  int bubble_sort_array_10_mil[10000], selection_sort_array_10_mil[10000], insertion_sort_array_10_mil[10000];
  int bubble_sort_array_50_mil[50000], selection_sort_array_50_mil[50000], insertion_sort_array_50_mil[50000];
  int bubble_sort_array_100_mil[100000], selection_sort_array_100_mil[100000], insertion_sort_array_100_mil[100000];

  int count, aux;

  // Prenche valores de entrada
  // - 10mil -
  for (count=0; count<=9999; count++) {
    scanf(", %d", &aux);
    bubble_sort_array_10_mil[count] = aux;
    selection_sort_array_10_mil[count] = aux;
    insertion_sort_array_10_mil[count] = aux;
  }
  // - 50mil -
  for (count=0; count<=49999; count++) {
    scanf(", %d", &aux);
    bubble_sort_array_50_mil[count] = aux;
    selection_sort_array_50_mil[count] = aux;
    insertion_sort_array_50_mil[count] = aux;
  }
  // - 100mil -
  for (count=0; count<=99999; count++) {
    scanf(", %d", &aux);
    bubble_sort_array_100_mil[count] = aux;
    selection_sort_array_100_mil[count] = aux;
    insertion_sort_array_100_mil[count] = aux;
  }

  // BUBBLE SORT
  bubble_sort_start = clock();
  bubble_sort(bubble_sort_array_10_mil, 10000);
  bubble_sort(bubble_sort_array_50_mil, 50000);
  bubble_sort(bubble_sort_array_100_mil, 100000);
  bubble_sort_end = clock();

  // SELECTION SORT
  selection_sort_start = clock();
  selection_sort(selection_sort_array_10_mil, 10000);
  selection_sort(selection_sort_array_50_mil, 50000);
  selection_sort(selection_sort_array_100_mil, 100000);
  selection_sort_end = clock();

  // INSERTION SORT
  insertion_sort_start = clock();
  insertion_sort(insertion_sort_array_10_mil, 10000);
  insertion_sort(insertion_sort_array_50_mil, 50000);
  insertion_sort(insertion_sort_array_100_mil, 100000);
  insertion_sort_end = clock();

  // Times
  double dif_tempo_bubble_sort = ((double) bubble_sort_end - bubble_sort_start)/CLOCKS_PER_SEC;
  double dif_tempo_selection_sort = ((double) selection_sort_end - selection_sort_start)/CLOCKS_PER_SEC;
  double dif_tempo_insertion_sort = ((double) insertion_sort_end - insertion_sort_start)/CLOCKS_PER_SEC;

  printf("\n\t BUBBLE SORT: Tempo em segundos: %lf", dif_tempo_bubble_sort);
  printf("\n\t SELECTION SORT: Tempo em segundos: %lf", dif_tempo_selection_sort);
  printf("\n\t INSERTION SORT: Tempo em segundos: %lf", dif_tempo_insertion_sort);

  return 0;
}
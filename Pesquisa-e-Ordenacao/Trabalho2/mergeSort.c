void intercala (int array[], int inicio, int meio, int fim) {
  
  // Declara variaveis e auxiliares
  int auxiliar[(fim - inicio + 1)];
  int i = inicio;
  int j = meio;
  int k = 0;

  while ( (i < meio) && (j <= fim) ){

    // Coloca maior no array auxiliar
    if ( array[i] <= array[j] ){
      auxiliar[k] = array[i];
      i++;

    } else {
      auxiliar[k] = array[j];
      j++;

    }

    // Acrescenta em k
    k++;
  }

  // Percorre colocando elemento na posição i no array auxiliar
  while ( i < meio ){
    auxiliar[k] = array[i];
    k++;
    i++;
  }

  // Percorre colocando elemento na posição j no array auxiliar
  while (j <= fim) {
    auxiliar[k] = array[j];
    k++;
    j++;
  }

  // Coloca valores do vetor auxiliar para o original 
  for (k = inicio; k <= fim; k++) {
    array[k] = auxiliar[k - inicio];
  }

}

void mergeSort (int array[], int inicio, int fim) {
  int meio;

  if (inicio < fim){
    meio = (inicio + fim) / 2;

    // Chama a função do inicio até o meio 
    mergeSort(array, inicio, meio);

    // Chama a função do meio até o fim 
    mergeSort(array, (meio + 1), fim);

    // Intercala os dois
    intercala(array, inicio, (meio + 1), fim);
  } 
}
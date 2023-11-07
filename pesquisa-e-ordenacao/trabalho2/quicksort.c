int particiona(int array[], int inicio, int fim) {
  
  // Criado variaveis e atribuido valores
  int pivo, k, i, aux;
  pivo = fim;
  k = inicio;

  // Percorre array
  for (i = inicio; i < fim; i++) {

    // Faz as trocas entre i e k
    if ( array[i] <= array[pivo] ){
      aux = array[i];
      array[i] = array[k];
      array[k] = aux;
      
      k++;
    }
  }

  // Realiza a troca de k pelo pivo
  if ( array[k] > array[pivo] ){
    aux = array[k];
    array[k] = array[pivo];
    array[pivo] = aux;
  }

  return k;
}

void quickSort (int array[], int inicio, int fim){
  int pivo;

  if (inicio < fim) {

    // Redefine o pivo
    pivo = particiona(array, inicio, fim);

    // Chama a função do inicio até a metade
    quickSort(array, inicio, (pivo - 1) );

    // Chama a função da metade até o fim
    quickSort(array, (pivo + 1), fim );
  }
}
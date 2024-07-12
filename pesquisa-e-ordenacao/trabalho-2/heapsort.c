void criaHeap(int array[], int i, int n){
  
  // Cria variaveis e faz atribuições
  int maior, left, right, aux;
  maior = i;
  left = (2 * i + 1);
  right = (2 * i + 2);

  // Troca maior por left
  if ( (left < n) && array[left] > array[i] ){
    maior = left;
  }

  // Troca maior por right
  if ( (right < n) && array[right] > array[maior] ){
    maior = right;
  } 

  // Faz a troca e chama Heap
  if ( maior != i ) {
    aux = array[i];
    array[i] = array[maior];
    array[maior] = aux;

    criaHeap(array, maior, n);
  }
}

void heapSort(int array[], int n){
  int k, aux;

  // Chama Heap
  for (k = (n / 2) - 1; k >= 0; k--){
    criaHeap(array, k, n);
  }

  // Faz a troca e chama Heap
  for (k = (n - 1); k >= 0; k--){
    
    aux = array[0];
    array[0] = array[k];
    array[k] = aux;

    criaHeap(array, 0, k);
  }
}
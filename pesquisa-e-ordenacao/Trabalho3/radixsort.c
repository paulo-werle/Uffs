// Define struct para produto
typedef struct {
  int code;
  char name[50];
} Product;

void printValues(Product array[], int n){
  // Cria variaveis auxiliares
  int i;

  // Percorre produtos para imprimir
  for (i = 0; i < n; i++){
    printf("%d - %s \n", array[i].code, array[i].name);
  }
}

void countingSort(Product array[], int n, int pos){
  // Cria variaveis auxiliares
  int i, digito;
  
  // Cria count e array auxiliar
  int count[10] = { 0 };
  Product aux[n];

  // Percorre array para fazer contagem
  for (i = 0; i < n; i++){
    digito = (array[i].code / pos) % 10;
    count[digito]++;
  }

  // Soma as ocorrencias
  for (i = 1; i < 10; i++){
    count[i] = count[i] + count[i-1];
  }

  // Forma array de saida
  for (i = (n-1); i >= 0; i-- ){
    digito = (array[i].code / pos) % 10;
    count[digito]--;
    aux[ count[digito] ].code = array[i].code;

    // aux[ count[digito] ].name = array[i].name;
    strcpy(aux[ count[digito] ].name, array[i].name);
  }

  // Coloca no array original
  for (i = 0; i < n; i++){
    // printf("Item %d: %d \n", i, array[i].code);
    array[i] = aux[i];

  }
}

int buscaMax(Product array[], int n){
  // Cria variaveis auxiliares
  int max, i;

  // Coloca primeiro valor sendo o maior
  max = array[0].code;

  // Percorre array, e caso achar um maior, define como maior
  for (i = 1; i <= n; i++){
    if (array[i].code > max){
      max = array[i].code;
    }
  }

  // Retorna o maior elemento
  return max;
}

void radixSort(Product array[], int n ){
  // Cria variaveis auxiliares
  int max, pos;

  // Chama função para achar o maior
  max = buscaMax(array, n);

  // Percorre count
  for(pos = 1; (max/pos) > 0; pos*=10){
    countingSort( array, n, pos);
  }
}
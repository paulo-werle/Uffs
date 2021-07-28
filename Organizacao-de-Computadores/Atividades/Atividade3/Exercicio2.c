#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// void preenche_vetor(int &vetor[0], int num_elementos);  
void preencheVetor(int vetor[], int num_elementos){
  // Inicia variaveis
  int i;

  // Coleta dados
  for (i = 0; i < num_elementos; i++){
    printf("Digite um valor para colocar no vetor: ");
    scanf("%d", &vetor[i]);
  }
}

// void imprime_vetor(int &vetor[0], int num_elementos);
void imprimeVetor(int vetor[], int num_elementos){
  // Inicia variaveis
  int i;

  // Imprime dados
  for (i = 0; i < num_elementos; i++){
    printf("%d, ", vetor[i]);
  }
  printf("\n");
}

// void ordena_vetor(int &vetor[0], int num_elementos); 
void ordenaVetor(int vetor[], int num_elementos){
  // Inicia variaveis
  int i, j,aux;

  // Percorre dados
  for (i = 0; i < num_elementos; i++){ 
    for (j = 0; j < num_elementos; j++){

      // Troca elementos de posição
      if (vetor[i] > vetor[j]){
        aux = vetor[i]; 
        vetor[i] = vetor[j];
        vetor[j] = aux;  
      }
    }
  }
}

int main(){
  // Inicia variaveis
  int vetor[10];

  // Executa funções
  preencheVetor(vetor, 10);
  imprimeVetor(vetor, 10);
  ordenaVetor(vetor, 10);
  imprimeVetor(vetor, 10);

  return 0;
}
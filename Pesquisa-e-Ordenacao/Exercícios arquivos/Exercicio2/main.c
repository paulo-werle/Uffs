// 2. Faça um programa que leia um arquivo de texto contendo uma lista de compras. 
// Cada linha do arquivo possui nome, quantidade e valor unitário do produto. 
// O programa então exibe o total por produto e o total da compra. Linhas em branco devem ser ignoradas.
#include <stdio.h>
#include <stdlib.h>

int main(){
  int i;

  char product_name[50];
  int product_quantity;
  float product_price, total_value;

  // Abre arquivo para leitura
  FILE *read_archive = fopen("input.txt", "r");
  if(read_archive == NULL){
    printf("Erro ao abrir o arquivo!");
    exit(1);
  }
 
  // Percorre arquivo
  while( !feof(read_archive) ){
    
    // Le valores da linha do arquivo
    fscanf(read_archive, "%s - %d - %f\n", product_name, &product_quantity, &product_price);

    // Imprime nome do produto e a soma do produto
    printf("%s\n", product_name);
    printf("\t %d - %.2f = %.2f\n", product_quantity, product_price, (product_quantity * product_price) );
    printf("\n");

    // Atribui para soma total
    total_value += (product_quantity * product_price);
  }

  // Imprime soma total
  printf("--------------------------\n");
  printf("TOTAL: %.2f\n", total_value);

  // Fecha arquivo
  fclose(read_archive);

  return 0;
}
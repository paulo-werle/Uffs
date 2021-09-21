#include <stdio.h>

int guloso (int mat[][5], int origem, int destino, int numPassos, int numMax){

  // Caso queira utilizar a variavel caminha, para ir para 
  // o nodo especifico, não precisa iniciar ela com valor
	int j, caminha, menorValor = 1000; 

  if (numPassos >= numMax)
  { // Caso entrar aqui significa que ele andou demais
    // Retorna o numero para erro

    return 0;
  }

	for (j = 0; j < numMax; j++)
  { // Percorre matriz

		if ( mat[origem][j] != 0 && j != origem )
    { // Caso existir arresta, e o destino ser diferente da atual

      if ( mat[origem][j] < menorValor )
      { // Caso ser menor valor

        // Aqui vai guardar o menor valor
        // e vai atualizar qual é o cara que deve ir
        menorValor = mat[origem][j];
        caminha = j;
      } 
    }
  } 

  if ( menorValor == 0 )
  { // Caso for 0 significa que não tem arresta
    // Retorna valor para erro 
    return 0;
  } else {
    printf("%d) De %d, vai para %d\n", numPassos, origem, caminha);

    if (origem != destino)
    { // Caso o valor a ir sejá diferente do destino, deve executar novamente

      return guloso(mat, caminha, destino, ++numPassos, numMax);

    }
  }

    
  
  return 1;
}

int main() {
  int matAdja[5][5] = {
    { 0, 1, 0, 0, 0 },
    { 0, 0, 2, 0, 0 },
    { 1, 0, 0, 0, 2 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },        
  };                                                           
    
  int partida,chegada;
    
  printf("Partida,chegada: ");
  scanf("%d,%d",&partida,&chegada);
  
  int busca = guloso(matAdja, (partida - 1), (chegada - 1), 1, 5);
  
  if (busca == 0) {
    printf("\nCansei, impossível fazer com Guloso\n");
  
  } else if (busca == 1) {
    printf("\nEncontrei\n");
  
  } else {

    printf("\nCansei, impossível fazer com Guloso!\n");
  } 
  

  return 0;
}
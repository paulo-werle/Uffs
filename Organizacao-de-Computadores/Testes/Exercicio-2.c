#include <stdio.h>


int main(){

  int vetor_A[12] = {2, 59, 39, 48, 25, 67, 19, 76, 52, 65, 18, 99};
  int sumInpar = 0;
  int sumPar = 0; 
  int count = 0;

  while(count < 12){
    if ( (vetor_A[count] % 2) == 1 ){
      sumInpar = sumInpar + vetor_A[count];
    } else {
      sumPar = sumPar + vetor_A[count];
    }
    count = count + 1;
  }

  printf("Soma dos impares: %d\n", sumInpar);
  printf("Soma dos pares: %d\n", sumPar);

  return 0;
}
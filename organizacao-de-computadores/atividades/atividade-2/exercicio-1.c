#include <stdio.h>


int main(){

  int count, sum;
  count = 11;
  sum = 0;

  while(count < 100){

    sum = sum + count;
    count = count + 2;
  }

  printf("%d", sum);
  return 0;
}
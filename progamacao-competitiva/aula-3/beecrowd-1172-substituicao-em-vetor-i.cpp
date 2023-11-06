#include <iostream>

using namespace std;

int main() {

  // Cria e preenche vetor
  int array[10];
  for (int i = 0; i < 10; i++) {
    cin >> array[i];
  }

  // Percorre valores para manipular o valor
  for (int i = 0; i < 10; i++) {
    if (array[i] <= 1) {
      array[i] = 1;
    }

    printf("X[%d] = %d", i, array[i]);
    cout << endl;
  }

  return 0;
}
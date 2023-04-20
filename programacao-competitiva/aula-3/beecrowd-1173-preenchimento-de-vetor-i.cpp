#include <iostream>

using namespace std;

int main() {

  // Cria e preenche valores
  int array[10];
  cin >> array[0];

  // Percorre valores para manipular o valor
  for (int i = 0; i < 10; i++) {
    if (i) {
      array[i] = array[i - 1] * 2;
    }

    printf("N[%d] = %d", i, array[i]);
    cout << endl;
  }

  return 0;
}
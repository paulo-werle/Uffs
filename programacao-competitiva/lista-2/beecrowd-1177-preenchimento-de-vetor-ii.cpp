// Problema 1177 - Preenchimento de Vetor II

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t;
  vector <int> numbers(1000, 0);
  cin >> t;

  for (int i = 0; i < 1000; i++) {
    numbers[i] = (i % t);

    printf("N[%d] = %d", i, numbers[i]);
    cout << endl;
  }

  return 0;
}
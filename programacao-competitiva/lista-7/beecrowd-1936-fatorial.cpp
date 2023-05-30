#include <iostream>
#include <vector>

using namespace std;

int main() {
  int N;
  cin >> N;

  // Inicia variaveis
  vector<int> factorials;
  int factorial = 1;
  int i = 1;

  // Calcula e guarda fatoriais de 1 a N
  while (factorial <= N) {
    factorials.push_back(factorial);
    i++;
    factorial *= i;
  }

  // Encontra a quantidade mínima de números fatoriais cuja soma é igual a N
  int quantity = 0;
  for (int j = factorials.size() - 1; j >= 0; j--) {
    quantity += N / factorials[j];
    N %= factorials[j];
  }

  // Imprime quantidade
  cout << quantity << endl;

  return 0;
}
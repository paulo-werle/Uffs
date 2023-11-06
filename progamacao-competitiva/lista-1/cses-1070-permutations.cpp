// Problema 1070 - Permutations

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;

  // Verifica se n é 2 ou 3 (casos especiais)
  if (n == 2 || n == 3) {
    cout << "NO SOLUTION";
    return 0;
  }

  // Cria um array com os números de 1 até n
  int nums[n];
  for (int i = 0; i < n; i++) {
    nums[i] = i+1;
  }

  // Imprime os números ímpares seguidos dos números pares
  for (int i = 1; i < n; i += 2) {
    cout << nums[i] << " ";
  }
  for (int i = 0; i < n; i += 2) {
    cout << nums[i] << " ";
  }

  return 0;
}
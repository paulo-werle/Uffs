// Problema 1083 - Missing Number

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  int n;
  cin >> n;

  // Cria um vetor com n - 1 posições
  vector <int> nums(n - 1);

  // Atribui valores para o vetor
  for (int i = 0; i < (n - 1); i++) {
    cin >> nums[i];
  }

  // Ordena o vetor
  sort(nums.begin(), nums.end());

  // Percorre vetor testando se o numero está faltando
  for (int i = 1; i <= n; i++) {
    if (nums[i-1] != i) {
      cout << i << endl;
      break;
    }
  }

  return 0;
}
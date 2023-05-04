#include <iostream>
#include <algorithm>
using namespace std;

int main() {
  int n, x;
  cin >> n >> x;

  // Cria e le valores para armazenar pesos
  int weights[n];
  for (int i = 0; i < n; i++) {
    cin >> weights[i];
  }

  // Ordena os pesos das crianças
  sort(weights, weights + n);

  int left = 0, right = n-1;
  int gondolas = 0;

  // Enquanto ainda há crianças para serem colocadas nas gôndolas
  while (left <= right) {
    // Se a soma dos pesos das duas crianças mais leve e mais pesada couber em uma gôndola
    if (weights[left] + weights[right] <= x) {
      left++;
      right--;

    // Se não couberem, adiciona uma gôndola só com a criança mais pesada
    } else {
      right--;
    }

    // Adiciona uma gôndola
    gondolas++;
  }

  cout << gondolas << endl;

  return 0;
}

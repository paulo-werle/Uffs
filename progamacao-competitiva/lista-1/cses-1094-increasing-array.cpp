// Problema 1094 - Increasing Array

#include <iostream>

using namespace std;

int main() {
  int n;
  cin >> n;

  // Cria e preenche um vetor com n posições
  long int array[n];
  for (int i = 0; i < n; i++) {
    cin >> array[i];
  }

  // Cria uma variavel para a quantidade de movimentos necessarios
  // E um controle para o elemento maximo
  long long int moves = 0;
  long int max_element = array[0];

  for (int i = 1; i < n; i++) {
    if (array[i] < max_element) {
      moves += max_element - array[i];
    }
    else {
      max_element = array[i];
    }
  }

  // Imprime movimentos minimos necessarios
  cout << moves << endl;

  return 0;
}
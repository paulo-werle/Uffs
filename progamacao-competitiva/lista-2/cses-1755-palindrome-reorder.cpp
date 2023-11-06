// Problema 1755 - Palindrome Reorder

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  string s;
  cin >> s;

  // Cria um vetor de inteiros
  vector<int> freq(26);

  // Preenche o vetor freq com a frequência de cada letra na string
  for (char c : s) {
    ++freq[c - 'A'];
  }

  // Conta quantas letras aparecem um número ímpar de vezes na string
  int odd = 0;
  for (int f : freq) {
    odd += (f % 2);
  }

  // Se houver mais de uma letra com frequência ímpar, não é possível formar um palíndromo
  if (odd > 1) {
    cout << "NO SOLUTION\n";
    return 0;
  }

  // Cria uma nova string para armazenar o palíndromo
  string result(s.size(), ' ');

  // Define índices iniciais para o começo e o fim da string result
  int i = 0, j = s.size() - 1;

  // Itera sobre cada letra do alfabeto
  for (int k = 0; k < 26; ++k) {
    char c = k + 'A';

    // Se a frequência da letra for ímpar, coloca a letra no meio da string result
    if (freq[k] % 2 == 1) {
      result[s.size() / 2] = c;
    }

    // Adiciona a letra metade da quantidade de vezes no começo e metade no fim da string result
    for (int l = 0; l < freq[k] / 2; ++l) {
      result[i++] = result[j--] = c;
    }
  }

  cout << result << "\n";
  return 0;
}
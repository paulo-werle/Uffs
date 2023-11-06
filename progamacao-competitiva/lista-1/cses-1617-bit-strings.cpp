// Problema 1617 - Bit Strings

#include <iostream>

using namespace std;

const int mod = 1e9 + 7;

int main() {
  int n;
  cin >> n;

  // Inicia variavel para resposta
  long long int ans = 1;
  for (int i = 0; i < n; i++) {
    // Calcula o equivalente a 2^n, e faz a operação % para evitar um overflow
    ans = (ans * 2) % mod;
  }

  cout << ans << endl;

  return 0;
}
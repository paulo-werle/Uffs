// Problema 1754 - Coin Piles

#include <iostream>

using namespace std;

int main() {
  int t;
  cin >> t;

  // Percorre enquanto maior que 0
  while (t--) {
    int a, b;
    cin >> a >> b;
    int sum = a + b;

    // Verifica se é possivel tirar 3 moedas das pilhas
    // Verifica se é possivel tirar o numero suficiente de moedas de
    // cada pilha em relação a outra pilha
    if (sum % 3 == 0 && 2*a >= b && 2*b >= a) {
      cout << "YES\n";

    } else {
      cout << "NO\n";

    }
  }
  return 0;
}
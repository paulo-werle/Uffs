// Problema 1471 - Mergulho

#include <iostream>
#include <vector>

using namespace std;

int main() {
  int n;
  int r;

  // Fica no laço enquanto ter entradas de n e r
  while (cin >> n >> r) {
    vector <bool> divers(n, false);

    // Coloca valores no divers
    int aux = 0;
    for (int i = 0; i < r; i++) {
      cin >> aux;
      divers[aux - 1] = true;
    }

    // Caso seja false imprime
    bool empty = true;
    for (int i = 0; i < n; i++) {
      if (!divers[i]) {
        cout << i + 1 << ' ';
        empty = false;
      }
    }

    // Caso todos for true
    if (empty) {
      cout << '*';
    }

    cout << endl;
  }

  return 0;
}
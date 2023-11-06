#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> pares;
  vector<int> impares;

  int n;
  for (int i = 0; i < 15; i++) {
    cin >> n;

    // Verifica qual tipo para colocar no vetor
    if (n % 2 == 0) {
      pares.push_back(n);
    } else {
      impares.push_back(n);
    }

    // Verifica se precisa imprimir e limpar o vetor
    if (pares.size() == 5) {
      for (int j = 0; j < 5; j++) {
        cout << "par[" << j << "] = " << pares[j] << endl;
      }
      pares.clear();
    }

    // Verifica se precisa imprimir e limpar o vetor
    if (impares.size() == 5) {
      for (int j = 0; j < 5; j++) {
        cout << "impar[" << j << "] = " << impares[j] << endl;
      }
      impares.clear();
    }
  }

  // Imprime os valores restantes
  for (int i = 0; i < impares.size(); i++) {
    cout << "impar[" << i << "] = " << impares[i] << endl;
  }

  // Imprime os valores restantes
  for (int i = 0; i < pares.size(); i++) {
    cout << "par[" << i << "] = " << pares[i] << endl;
  }

  return 0;
}
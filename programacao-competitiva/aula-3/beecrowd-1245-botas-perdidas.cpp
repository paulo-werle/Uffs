#include <iostream>
#include <map>

using namespace std;

int main() {
  int n;

  while (cin >> n) {
    map<int, int> sapatos;
    int tamanho, num_sapatos;
    char pe;

    // Lê os sapatos e armazena em um map
    for (int i = 0; i < n; i++) {
      cin >> tamanho >> pe;

      if (sapatos.count(tamanho) == 0) {
        sapatos[tamanho] = 0;
      }
      if (pe == 'E') {
        sapatos[tamanho]++;
      } else {
        sapatos[tamanho]--;
      }
    }

    // Calcula o número de pares
    int num_pares = 0;
    for (auto it : sapatos) {
      if (it.second >= 0) {
        num_pares += it.second;
      } else {
        num_pares += -it.second;
      }
    }

    cout << num_pares << endl;
  }

  return 0;
}
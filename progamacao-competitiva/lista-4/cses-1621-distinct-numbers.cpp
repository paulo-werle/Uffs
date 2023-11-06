#include <iostream>
#include <set>

using namespace std;

int main() {
  int n;
  cin >> n;

  // Cria um set vazio para armazenar os valores distintos
  set <int> distinctNumbers;

  for (int i = 0; i < n; i++) {
    // Lê o próximo elemento na sequência
    int x;
    cin >> x;

    // Insere o elemento no set, como ele não permite elementos duplicados
    // Apenas um elemento com cada valor será inserido
    distinctNumbers.insert(x);
  }

  cout << distinctNumbers.size() << endl;

  return 0;
}
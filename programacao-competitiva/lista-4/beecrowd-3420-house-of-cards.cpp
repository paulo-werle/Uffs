#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int t, c, inicio, fim, index, quantidade;
  cin >> t;

  while (--t) {
    cin >> c;
    inicio = 1;
    fim = sqrt(c);

    index = (inicio - fim) / 2;
    quantidade = ( 3 * index ^ 2 + index) / 2;

    while( inicio <= fim) {
      cout << inicio << " " << fim << endl;
      cout << quantidade << " " << c << endl;

      if (quantidade == c)
        break;

      else if (quantidade > c)
        fim = quantidade - 1;

      else if (quantidade < c)
        inicio = quantidade + 1;
    }

    if (inicio > fim) {
      index = fim
    }
  }

  return 0;
}
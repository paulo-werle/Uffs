// Problema 1071 - Number Spiral

#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    long long y, x;
    cin >> y >> x;

    long long ans;
    // Caso em que a coluna x é maior do que a linha y
    if (x > y) {

      // Se a coluna x é ímpar
      // Calcula o número na célula (y, x)
      if (x % 2 == 1) {
        ans = x * x - y + 1;

      // Se a coluna x é par
      // Decrementa e calcula o número na célula (y, x)
      } else {
        x--;
        ans = x * x + y;
      }

    // Caso em que a linha y é maior do que a coluna x
    } else {
      // Se a linha y é par
      // Calcula o número na célula (y, x)
      if (y % 2 == 0) {
        ans = y * y - x + 1;

      // Se a linha y é ímpar
      // Decrementa e calcula o número na célula (y, x)
      } else {
        y--;
        ans = y * y + x;
      }
    }

    cout << ans << endl;
  }

  return 0;
}
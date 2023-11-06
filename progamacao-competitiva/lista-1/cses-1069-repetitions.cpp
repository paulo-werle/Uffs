// Problema 1069 - Repetitions

#include <iostream>

using namespace std;

int main() {
  std::string s;
  getline(cin, s);

  int bigger = 1, count = 1;

  for (int i = 1; i < s.length(); i++) {

    // Se o caractere atual for igual ao anterior
    if (s[i] == s[i - 1]) {
      count++;
      bigger = max(bigger, count);

    // Se o caractere atual for diferente do anterior
    } else {
      count = 1;
    }
  }

  // Imprime o tamanho da maior sequência de caracteres idênticos
  cout << bigger << endl;

  return 0;
}
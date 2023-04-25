// Problema 1069 - Diamantes e Areia

#include <iostream>
#include <stack>

using namespace std;

int main() {
  int n;
  cin >> n;

  // Percorre quantidade de casos
  while (n--) {
    string s;
    cin >> s;
    int cnt = 0;
    stack<char> st;

    // Percorre string
    for (char c : s) {

      // Caso encontrar o caracter < adiciona na pilha
      if (c == '<') {
        st.push(c);

      // Caso encontrar o caracter > e a pilha não estiver vazia
      // Remove o item adicionado <
      // E incrementa o contador
      } else if (c == '>' && !st.empty()) {
        st.pop();
        cnt++;

      }
    }

    cout << cnt << endl;
  }
  return 0;
}
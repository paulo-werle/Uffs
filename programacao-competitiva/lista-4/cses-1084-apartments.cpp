#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
  // Leitura dos valores de n, m e k
  int n, m, k;
  cin >> n >> m >> k;

  // Criação e leitura dos vetores a e b
  vector <int> a(n), b(m);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  for (int i = 0; i < m; i++) {
    cin >> b[i];
  }

  // Ordenação dos vetores a e b
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  // Variáveis i e j são índices que percorrem os vetores a e b, respectivamente
  // Variável ans é o número de pares de apartamentos encontrados
  int i = 0, j = 0, ans = 0;

  // Executa enquanto não tiver percorrido um dos vetores inteiros
  while (i < n && j < m) {

    // Se a diferença entre os elementos é menor ou igual a k
    // Incrementamos ans e avançamos nos dois vetores
    if (abs(a[i] - b[j]) <= k) {
      ans++;
      i++;
      j++;

    // Se o elemento de a é menor que o elemento de b
    // Avançamos no vetor a
    } else if (a[i] < b[j]) {
      i++;

    // Caso contrário, o elemento de b é menor que o de a
    // Avançamos no vetor b
    } else {
      j++;
    }
  }

  cout << ans << endl;

  return 0;
}

#include <iostream>
#include <vector>

using namespace std;

int calcularLucroMaximo(int N, int C, const vector<int>& cotacoes) {
  int lucroMaximo = 0;
  int acoesCompradas = 0;

  // Inicializa o preço de compra com a primeira cotação
  int precoCompra = cotacoes[0];

  // Percorre as cotações a partir do segundo dia
  for (int i = 1; i < N; i++) {

    // Atualiza o preço de compra se a cotação atual for menor
    if (cotacoes[i] < precoCompra) {
      precoCompra = cotacoes[i];

    // Se a diferença entre a cotação atual, o preço de compra e a taxa fixa for maior que zero, indica que há lucro na venda
    } else if (cotacoes[i] - precoCompra - C > 0) {

      // Adiciona o lucro ao lucro máximo
      lucroMaximo += cotacoes[i] - precoCompra - C;
      // Atualiza o preço de compra após a compra da ação
      precoCompra = cotacoes[i] - C;
    }
  }

  return lucroMaximo;
}

int main() {
  int N, C;
  cin >> N >> C;

  vector<int> cotacoes(N);
  for (int i = 0; i < N; i++) {
    cin >> cotacoes[i];
  }

  int lucroMaximo = calcularLucroMaximo(N, C, cotacoes);
  cout << lucroMaximo << endl;

  return 0;
}

#include <iostream>
#include <vector>

using namespace std;

struct Atracao {
  int duracao;
  int pontuacao;
};

int calcularPontuacaoMaxima(int tempoDisponivel, const vector<Atracao>& atracoes) {
  int n = atracoes.size();
  vector<vector<int>> dp(n + 1, vector<int>(tempoDisponivel + 1, 0));

  // Preencher a tabela dinâmica "dp" usando programação dinâmica
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= tempoDisponivel; j++) {
      if (atracoes[i - 1].duracao <= j) {

        // Se a duração da atração for menor ou igual ao tempo disponível,
        // escolher entre incluir ou não a atração na solução ótima
        dp[i][j] = max(dp[i - 1][j], atracoes[i - 1].pontuacao + dp[i][j - atracoes[i - 1].duracao]);

      } else {

        // Se a duração da atração for maior do que o tempo disponível,
        // não é possível incluir essa atração
        dp[i][j] = dp[i - 1][j];

      }
    }
  }

  // Retornar a pontuação máxima possível
  return dp[n][tempoDisponivel];
}

int main() {
  int instancia = 1;
  int N, T;

  while (cin >> N >> T && N != 0) {
    vector<Atracao> atracoes(N);

    // Ler os dados das atrações
    for (int i = 0; i < N; i++) {
      cin >> atracoes[i].duracao >> atracoes[i].pontuacao;
    }

    // Calcular a pontuação máxima possível
    int pontuacaoMaxima = calcularPontuacaoMaxima(T, atracoes);

    // Imprimir a saída
    cout << "Instancia " << instancia++ << endl;
    cout << pontuacaoMaxima << endl;
    cout << endl;
  }

  return 0;
}

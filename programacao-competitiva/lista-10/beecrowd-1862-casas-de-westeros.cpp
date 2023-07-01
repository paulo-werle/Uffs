#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define true 1
#define false 0
#define MAXSIZE 1010

// Vetor para armazenar o grau de cada casa
vector<int> bor(MAXSIZE);

// Vetor para marcar as casas visitadas
vector<char> vis(MAXSIZE);

// Matriz de adjacência para representar as conexões entre as casas
vector<vector<char>> adj(MAXSIZE, vector<char>(MAXSIZE));

int n;
int vertices, arestas;

// Função de comparação para ordenar os resultados finais
bool compare(const int& a, const int& b) {
  return b < a;
}

// Função de busca em profundidade (DFS)
void dfs(int u) {
  int i;
  vis[u] = true;
  ++vertices;
  arestas += bor[u];

  for (i = 0; i < n; ++i) {
    if (adj[u][i]) {
      if (!vis[i]) {
        dfs(i);
      }
    }
  }
}

int main(int argc, char **argv) {
  int i, j;
  char c[MAXSIZE];

  // Leitura do número de casas
  cin >> n;
  cin.ignore();

  // Leitura das conexões entre as casas e cálculo do grau de cada casa
  for (i = 0; i < n; ++i) {
    cin >> c;
    for (j = 0; c[j]; ++j) {
      if (i != j && c[j] == 'S') {
        adj[i][j] = true;
        ++bor[i];
      }
    }
  }

  vector<int> ans;

  // Verificação das componentes conectadas e cálculo dos resultados
  for (i = j = 0; i < n; ++i) {
    if (!vis[i]) {
      vertices = arestas = 0;
      dfs(i);

      // Verificação se a componente é uma árvore
      if (vertices * (vertices - 1) != arestas) {
        cout << "-1" << endl;
        return 0;
      }

      ans.push_back(vertices);
      j++;
    }
  }

  // Ordenação dos resultados finais em ordem decrescente
  sort(ans.begin(), ans.end(), compare);

  // Impressão dos resultados finais
  cout << j << endl;
  for (i = 0; i < j; ++i) {
    cout << ans[i] << (i < j - 1 ? ' ' : '\n');
  }

  return 0;
}

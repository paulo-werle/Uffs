#include <iostream>
#include <vector>

using namespace std;

// Função de busca em profundidade (DFS)
void depthFirstSearch(int v, vector<vector<int>>& adjList, vector<int>& visited) {
  visited[v] = 1;

  for (auto u : adjList[v]) {
    if (visited[u] == 0) {
      depthFirstSearch(u, adjList, visited);
    }
  }
}

// Função para contar o número de salas no mapa
int countRooms(vector<vector<char>>& map, int n, int m) {
  // Lista de adjacência
  vector<vector<int>> adjList(n * m);

  // Vetor de visitados
  vector<int> visited(n * m, 0);
  int roomCount = 0;

  // Construção da lista de adjacência
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int v = i * m + j;

      if (map[i][j] == '.') {
        if (i > 0 && map[i - 1][j] == '.') {
          int u = (i - 1) * m + j;
          adjList[v].push_back(u);
          adjList[u].push_back(v);
        }

        if (i < n - 1 && map[i + 1][j] == '.') {
          int u = (i + 1) * m + j;
          adjList[v].push_back(u);
          adjList[u].push_back(v);
        }

        if (j > 0 && map[i][j - 1] == '.') {
          int u = i * m + (j - 1);
          adjList[v].push_back(u);
          adjList[u].push_back(v);
        }

        if (j < m - 1 && map[i][j + 1] == '.') {
          int u = i * m + (j + 1);
          adjList[v].push_back(u);
          adjList[u].push_back(v);
        }
      }
    }
  }

  // Contagem do número de salas
  for (int i = 0; i < n * m; i++) {
    if (visited[i] == 0 && map[i / m][i % m] == '.') {
      depthFirstSearch(i, adjList, visited);
      roomCount++;
    }
  }

  return roomCount;
}

int main() {
  int n, m;
  cin >> n >> m;

  vector<vector<char>> map(n, vector<char>(m));

  // Leitura do mapa
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> map[i][j];
    }
  }

  int roomCount = countRooms(map, n, m);
  cout << roomCount << endl;

  return 0;
}

#include <iostream>
#include <vector>
#define N 8

using namespace std;

// Inicia variaveis
int n = N;
int count = 0;

vector<int> col(N);
vector<int> diag1(2*N-1);
vector<int> diag2(2*N-1);

vector<vector<char>> spaces;

void search(int r) {
  if (r == n) {
    // Incrementa quantidade
    count++;

  } else {

    // Percorre colunas
    for (int c = 0; c < n; c++) {

      // Testa se já tem rainha na coluna, ou nas diagonais
      if (col[c] || diag1[c+r] || diag2[c-r+n-1] || spaces[r][c] == '*') continue;

      col[c] = diag1[c+r] = diag2[c-r+n-1] = 1;
      search(r+1);
      col[c] = diag1[c+r] = diag2[c-r+n-1] = 0;
    }
  }
}

int main() {

  // Criando variavel auxiliar
  char aux;

  // Percorrendo linhas
  for (int indeX = 0; indeX < N; indeX++) {
    vector<char> space;

    // Percorrendo colunas
    for (int indeY = 0; indeY < N; indeY++) {

      // Inserindo no vetor
      cin >> aux;
      space.push_back(aux);
    }

    // Inserindo vetor na matriz
    spaces.push_back(space);
  }

  search(0);
  cout << count << endl;

  return 0;
}
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// Estrutura para contar as medalhas de um país
struct MedalCount {
  int gold;
  int silver;
  int bronze;

  // Construtor para inicializar com 0 medalhas
  MedalCount() : gold(0), silver(0), bronze(0) {}
};

bool compareCountries(const pair<string, MedalCount>& a, const pair<string, MedalCount>& b) {
  // Compara pelo número de medalhas de ouro
  if (a.second.gold != b.second.gold) {
    return a.second.gold > b.second.gold;

  // Compara pelo número de medalhas de prata
  } else if (a.second.silver != b.second.silver) {
    return a.second.silver > b.second.silver;

  // Compara pelo número de medalhas de bronze
  } else if (a.second.bronze != b.second.bronze) {
    return a.second.bronze > b.second.bronze;

  // Compara pelo nome do país em ordem alfabética
  } else {
    return a.first < b.first;
  }
}

int main() {
  map <string, MedalCount> medalTable;
  string eventName, gold, silver, bronze;

  // Lê o nome da prova e os países vencedores da prova enquanto houver entrada
  while (getline(cin, eventName)) {
    getline(cin, gold);
    getline(cin, silver);
    getline(cin, bronze);

    // Incrementa a quantidade de medalhas de cada país
    medalTable[gold].gold++;
    medalTable[silver].silver++;
    medalTable[bronze].bronze++;
  }

  // Converte o map para um vetor de pares (nome do país, estrutura MedalCount)
  vector<pair<string, MedalCount>> medalList(medalTable.begin(), medalTable.end());

  // Ordena o vetor de acordo com a quantidade de medalhas de ouro, prata e bronze
  // Caso haja empate, desempata comparando pela ordem alfabética do nome do país
  sort(medalList.begin(), medalList.end(), compareCountries);

  // Imprime o resultado
  cout << "Quadro de Medalhas" << endl;
  for (const auto& medal : medalList) {
    cout << medal.first << " " << medal.second.gold << " " << medal.second.silver << " " << medal.second.bronze << endl;
  }

  return 0;
}
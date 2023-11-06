#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

// Define a estrutura para armazenar informações de um país.
struct Country {
  string name;
  int gold, silver, bronze;
};

// Função para comparar dois países.
bool compareCountries(const Country& a, const Country& b) {
  // Compara a quantidade de medalhas de ouro.
  if (a.gold != b.gold) {
    return a.gold > b.gold;
  }

  // Compara a quantidade de medalhas de prata.
  if (a.silver != b.silver) {
    return a.silver > b.silver;
  }

  // Compara a quantidade de medalhas de bronze.
  if (a.bronze != b.bronze) {
    return a.bronze > b.bronze;
  }

  // Compara o nome alfabeticamente
  return a.name < b.name;
}

int main() {

  // Cria e lê o número de países.
  int n;
  cin >> n;

  // Cria um vetor de países.
  vector<Country> countries;

  // Loop para ler os dados de cada país.
  for (int i = 0; i < n; i++) {

    // Cria variavel auxiliar e le dados
    Country auxCountry;
    cin >> auxCountry.name;
    cin >> auxCountry.gold;
    cin >> auxCountry.silver;
    cin >> auxCountry.bronze;

    // Adiciona o país no vetor de países.
    countries.push_back(auxCountry);
  }

  // Ordena o vetor de países utilizando a função compareCountries como critério de comparação.
  sort(countries.begin(), countries.end(), compareCountries);

  // Loop para imprimir os dados de cada país.
  for (auto c : countries) {
    cout << c.name << " " << c.gold << " " << c.silver << " " << c.bronze << endl;
  }

  return 0;
}

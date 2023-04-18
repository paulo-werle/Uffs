#include <iostream>
#include <map>

using namespace std;

int main() {
  // Iniciando variaveis de controle
  int days, qnt, id;

  // Iniciando estrutura
  map<int, string> options {
    { 1, "Rolien"   },
    { 2, "Naej"     },
    { 3, "Elehcim"  },
    { 4, "Odranoel" }
  };

  // Pegando quantidade de dias de trabalho
  cin >> days;

  // Percorre quantidade de dias
  for (int i = 0; i < days; i++) {
    cin >> qnt;

    // Percorre tarefas por dia
    for (int j = 0; j < qnt; j++) {
      cin >> id;
      cout << options[id] << endl;
    }
  }

  return 0;
}
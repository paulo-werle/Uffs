// Problema 1861 - O Hall dos Assassinos
// Acho que esse ainda está com alguma coisa errada, mas não sei o que pode ser

#include <iostream>
#include <map>

using namespace std;

int main() {
  map <string, int> people;
  map <string, bool> killed;
  string assassin;
  string victim;

  // Insere valores recebidos na estrutura
  while (cin >> assassin >> victim) {
    people[assassin] += 1;
    killed[victim] = true;
  }

  // Imprime resultados
  cout << "HALL OF MURDERERS" << endl;

  // Imprime somente se o assacino não foi morto
  for (const auto& [key, value] : people) {
    if (!killed[key]) {
      cout << key << " " << value << endl;
    }
  }

  return 0;
}
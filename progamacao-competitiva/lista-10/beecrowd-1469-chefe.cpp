#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Função que realiza a busca em profundidade (DFS)
void depthFirstSearch(int current, const vector<vector<int>>& graph, vector<bool>& visited, const vector<int>& ages, int& min_age) {
  visited[current] = true;
  for (int i = 0; i < graph[current].size(); i++) {
    int neighbor = graph[current][i];
    min_age = min(min_age, ages[neighbor]);
    if (!visited[neighbor]) {
      depthFirstSearch(neighbor, graph, visited, ages, min_age);
    }
  }
}

// Função que troca as relações entre dois nomes
void swapRelations(int name1, int name2, vector<vector<int>>& graph) {
  swap(graph[name1], graph[name2]);
  for (int k = 1; k < graph.size(); k++) {
    for (int& neighbor : graph[k]) {
      if (neighbor == name1)
        neighbor = name2;
      else if (neighbor == name2)
        neighbor = name1;
    }
  }
}

int main() {
  int n_employee, n_relation, n_instruction;
  while (cin >> n_employee >> n_relation >> n_instruction) {
    vector<vector<int>> graph(n_employee + 1);
    vector<int> ages(n_employee + 1);

    // Lê as idades dos empregados
    for (int name = 1; name <= n_employee; name++) {
      int age;
      cin >> age;
      ages[name] = age;
    }

    // Lê as relações de subordinação
    for (int i = 0; i < n_relation; i++) {
      int a, b;
      cin >> a >> b;
      graph[b].push_back(a);
    }

    // Processa cada instrução
    for (int i = 0; i < n_instruction; i++) {
      string instruction;
      cin >> instruction;

      if (instruction == "T") {
        int name1, name2;
        cin >> name1 >> name2;
        swapRelations(name1, name2, graph);
      } else {
        int name;
        cin >> name;
        vector<bool> visited(graph.size(), false);
        int min_age = 101;
        depthFirstSearch(name, graph, visited, ages, min_age);
        if (min_age == 101)
          cout << "*" << endl;
        else
          cout << min_age << endl;
      }
    }
  }

  return 0;
}

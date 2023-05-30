// 5  12
// 6  10
// 8  15

// 0  5 = 5  => 7
// 5  6 = 11 => -1
// 11 8 = 19 => -4
// 2

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
  int duration;
  int deadline;
};

bool compareByDuration(const Task& task1, const Task& task2) {
  return task1.duration < task2.duration;
}

int main() {
  // Pega quantidade de tarefas
  int n;
  cin >> n;

  // Cria vetor de tarefas
  vector<Task> tasks(n);

  // Le durações e prazos
  for (int i = 0; i < n; i++) {
    cin >> tasks[i].duration >> tasks[i].deadline;
  }

  // Ordena pela duração
  sort(tasks.begin(), tasks.end(), compareByDuration);

  long long time = 0;
  long long reward = 0;

  for (int i = 0; i < n; i++) {
    time   += tasks[i].duration;
    reward += tasks[i].deadline - time;

    // cout << "time: " << time << endl;
    // cout << "reward: " << reward << endl;
    // cout << "\n";
  }

  cout << reward << endl;

  return 0;
}

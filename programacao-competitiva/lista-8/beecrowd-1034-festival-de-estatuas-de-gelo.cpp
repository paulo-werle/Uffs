#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int minBlocks(int desiredLength, const vector<int>& availableBlocks) {
  // Vetor de memorização
  vector<int> dp(desiredLength + 1, INT_MAX);

  // Caso base
  dp[0] = 0;

  for (int i = 1; i <= desiredLength; i++) {
    for (int j = 0; j < availableBlocks.size(); j++) {
      if (availableBlocks[j] <= i) {
        int subResult = dp[i - availableBlocks[j]];
        if (subResult != INT_MAX && subResult + 1 < dp[i]) {
          dp[i] = subResult + 1;
        }
      }
    }
  }

  return dp[desiredLength];
}

int main() {
  int numInstances;
  cin >> numInstances;

  for (int i = 0; i < numInstances; i++) {
    int numBlocks, desiredLength;
    cin >> numBlocks >> desiredLength;

    vector<int> availableBlocks(numBlocks);
    for (int j = 0; j < numBlocks; j++) {
      cin >> availableBlocks[j];
    }

    int minNumBlocks = minBlocks(desiredLength, availableBlocks);
    cout << minNumBlocks << endl;
  }

  return 0;
}
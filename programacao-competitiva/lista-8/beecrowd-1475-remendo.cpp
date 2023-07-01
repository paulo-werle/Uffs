#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;

    while (cin >> n && n != 0) {
        vector<vector<int>> grid(n, vector<int>(n, 0));
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        dp[0][0] = grid[0][0];

        // Preenchendo a primeira linha da matriz dp
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        // Preenchendo a primeira coluna da matriz dp
        for (int i = 1; i < n; i++) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        // Preenchendo o restante da matriz dp
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        cout << dp[n - 1][n - 1] << endl;
    }

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

int n = 3, m = 3;                 // grid size (as seen in screenshot)
int grid[3][3];

vector<vector<pair<int,int>>> dp;  // {minCost, direction}

// f(i,j) = minimum cost from (i,j) to (n-1,m-1)
int f(int i, int j) {

    // Out of bounds → invalid path
    if (i >= n || j >= m)
        return INF;

    // Reached destination
    if (i == n - 1 && j == m - 1)
        return grid[i][j];

    // Memoized
    if (dp[i][j].first != -1)
        return dp[i][j].first;

    int down = f(i + 1, j);
    int right = f(i, j + 1);

    if (down < right) {
        dp[i][j].second = 0;  // go down
    } else {
        dp[i][j].second = 1;  // go right
    }

    return dp[i][j].first = grid[i][j] + min(down, right);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Input grid
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j];

    dp.assign(n, vector<pair<int,int>>(m, {-1, -1}));

    cout << f(0, 0) << '\n';

    // Reconstruct path
    int i = 0, j = 0;
    while (!(i == n - 1 && j == m - 1)) {
        cout << i << " " << j << '\n';

        if (dp[i][j].second == 0)
            i++;      // down
        else
            j++;      // right
    }

    cout << i << " " << j << '\n';

    return 0;
}

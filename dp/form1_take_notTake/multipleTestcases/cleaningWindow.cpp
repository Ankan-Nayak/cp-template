/*### Problem Statement

Given an `N × M` grid of windows, `A[i][j]` is the time window `(i,j)` is cleaned. Cleaning causes dirty water to flow downward to nearby windows.

For every window, determine whether it is **clean (`1`) or dirty (`0`)** after all cleaning is finished.

### Constraints

* `1 ≤ T ≤ 1000`
* `1 ≤ N, M ≤ 1000`
* `1 ≤ A[i][j] ≤ N×M`
* Sum of `N×M` over all test cases ≤ `10⁷`

*/

##include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m;
vector<vector<int>> a, dp;

int rec(int x, int y) {
    if (x < 0 || y < 0 || y >= m)
        return 0;

    if (dp[x][y] != -1)
        return dp[x][y];

    int ans = 0;

    if (x > 0) {
        ans = max({
            rec(x - 1, y),
            rec(x - 1, y - 1),
            rec(x - 1, y + 1)
        });
    }

    return dp[x][y] = max(ans, a[x][y]);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;

    while (tc--) {
        cin >> n >> m;

        a.assign(n, vector<int>(m));
        dp.assign(n, vector<int>(m, -1));

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                int ans = 0;

                if (i > 0) {
                    ans = max({
                        rec(i - 1, j),
                        rec(i - 1, j - 1),
                        rec(i - 1, j + 1)
                    });
                }

                cout << (a[i][j] > ans ? 1 : 0) << ' ';
            }

            cout << '\n';
        }
    }

    return 0;
}
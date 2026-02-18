/* thinking process
1. always think Recursive DP and relation -> f(i, j) = min(1 + f(i - k, j) + f(k, j), 1 + f(i, j - k) + f(i, k))
2. think base cases also from RECURSIVE DP -> when i == j return 0 => dp[i][j] = 0 (if i == j)
3. think order of loop from RECURSIVE DP

4. convert all this logic now in ITERATIVE DP, carefull for boundary
5. take best case as BASE CASE, rest un-reachable cases should remain un reachable(inf or -inf)
6. Don't update random cases as base because during updation ans might change
*/


#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;

signed main() {

    int n, m;
    cin >> n >> m;

    vector<vector<int>> dp(n+10, vector<int>(m+10, inf));
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i == j) dp[i][j] = 0;
            else {
                for (int k = 0; k <= max(n, m); ++k) {
                    if (k <= i) dp[i][j] = min(dp[i][j], 1 + dp[i - k][j] + dp[k][j]);
                    if (k <= j) dp[i][j] = min(dp[i][j], 1 + dp[i][j - k] + dp[i][k]);
                }
            }
        }
    }
    cout << dp[n][m];
    return 0;
}

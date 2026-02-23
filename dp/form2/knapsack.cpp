#include<bits/stdc++.h>
using namespace std;
 
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n, x;
    cin >> n >> x;
    vector<int> prc(n + 1), pge(n + 1);
    for (int i = 1; i <= n; ++i) cin >> prc[i];
    for (int i = 1; i <= n; ++i) cin >> pge[i];
    vector<vector<int>> dp(n+2, vector<int>(x+2,0));
  
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= x; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j - prc[i] >= 0) dp[i][j] = max(dp[i][j], dp[i - 1][j - prc[i]] + pge[i]);
        }
    }
    cout << dp[n][x];
    return 0;
}
 
// dp[i][x] = max page till index spending at max x
// f(i, x) = max(i - 1, x) + f(i - 1, x - y[i])
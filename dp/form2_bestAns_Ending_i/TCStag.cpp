#include<bits/stdc++.h>
using namespace std;

int inf = 10000;
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> power(n + 1), toxic(n + 1);
    for (int i = 1; i <= n; ++i) cin >> power[i];
    for (int i = 1; i <= n; ++i) cin >> toxic[i];
    vector<vector<int>> dp(n+2, vector<int>(k+2,-inf));
    
    dp[0][0] = 0;
    if (power[1] <= k) dp[1][power[1]] = toxic[1];

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j]);
            if (j - power[i] >= 0) {
                if (i >= 2  &&  dp[i - 2][j - power[i]] != -inf) dp[i][j] = max(dp[i - 2][j - power[i]] + toxic[i], dp[i][j]);
            }
        }
    }

    cout << ((dp[n][k]) >= 0 ? dp[n][k] : -1) << endl;
    if (dp[n][k] == -1) return 0;

    int i = n, j = k;

    vector<int> ind_path;

    while (i > 0  &&  j > 0) {
        if (i == 1  && j == power[1]) {
            ind_path.push_back(i);
            break;
        }
        else if (j >= power[i]  &&  i >= 2  &&  dp[i][j] == dp[i - 2][j - power[i]] + toxic[i]) {
            ind_path.push_back(i);
            j -= power[i];
            i -= 2;
        }
        else if (dp[i][j] == dp[i - 1][j]) {
            i -= 1;
        } else {
            i -= 1;
        }
    }

    reverse(ind_path.begin(), ind_path.end());

    for (int i = 0; i < ind_path.size(); ++i) {
        cout << ind_path[i] << ' ';
    }
    
    return 0;
}
 


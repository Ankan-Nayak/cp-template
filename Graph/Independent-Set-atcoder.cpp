#include<bits/stdc++.h>
using namespace std;

#define int long long
const int M = 1e9+7;
const int N = 1e5+5;

vector<int> g[N];
int dp[N][2];

void dfs (int v, int par = -1) {
    // base case
    dp[v][0] = 1, dp[v][1] = 1;
    
    for (auto child : g[v]) {
        if (child == par) continue;
        dfs(child, v);
        dp[v][0] = 1LL * dp[v][0] * (dp[child][0] + dp[child][1]) % M;
        dp[v][1] = 1LL * dp[v][1] * dp[child][0] % M;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1);
    cout << (dp[1][0] + dp[1][1]) % M;

    return 0;
}

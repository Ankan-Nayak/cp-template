#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> vis;
int n, m;
vector<int> topo;

void dfs_topo(int node)
{
    vis[node] = 1;
    for (auto v : g[node])
    {
        if (!vis[v])
        {
            dfs_topo(v);
        }
    }
    topo.push_back(node);
}

int dp[100000]; // longest path starting at node
int rec(int node) {
    if (dp[node] != -1) return dp[node];
    int ans = 1;
    for (auto child : g[node]) {
        ans = max(ans, 1 + rec(child));
    }
    return dp[node] = ans;
}


int main()
{
    cin >> n >> m;
    g.resize(n + 1);
    vis.assign(n + 1, 0);

    for (int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        g[l].push_back(r);
    }

    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            dfs_topo(i);
        }
    }
    reverse(topo.begin(), topo.end());

    for (int i = 0; i < topo.size(); i++)
    {
        cout << topo[i] << " ";
    }


    // recursive
    memset(dp, -1, sizeof(dp));
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, rec(i));
    }
    cout << ans << '\n';


    // iterative
    for (auto node : topo) {
        for (auto child : g[node]) {
            dp[child] = max(dp[child], 1 + dp[node]);
        }
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans = max(ans, dp[i]);
    }
    // node count, edge count = ans - 1
}
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
bool vis[N];
vector<int> g[N];

int depth[N];

void dfs(int vertex, int par = -1) {
    for (auto child : g[vertex]) {
        if (child == par) continue;
        depth[child] = depth[vertex] + 1;
        dfs(child, vertex); 
    }
}


signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    // root node 1 here
    dfs(1);

    int mx_depth = -1;
    int mx_depth_node;
    for (int i = 1; i <= n; ++i) {
        if (mx_depth <depth[i]) {
            mx_depth = depth[i];
            mx_depth_node = i;
        }
        // reset
        depth[i] = 0;
    }

    dfs(mx_depth_node);

    for (int i = 1; i <= n; ++i) {
        if (mx_depth <depth[i]) {
            mx_depth = depth[i];
            mx_depth_node = i;
        }
    }

    cout << mx_depth << '\n';
}
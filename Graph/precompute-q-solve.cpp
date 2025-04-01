// Approach:
// - for precompute from parents, and compare (kind of x[v] > m) values in every vertex wrt to parent
// - we can go every vertex and do the required precomputation
// - add extra node in every leaf node (height = 0) and make them new leaf node 
// - new leaf node height = 0, prev actual leaf node height = 1;



#include<bits/stdc++.h>
using namespace std;

const int N = 2e5+10;
vector<int> g[N];
int hzrd[N];
int depth[N];
int height[N];
int n, m, k;

void dfs_ans(int vertex, int par = 0) {
    if (depth[par] == -1) {
        depth[vertex] = -1;
    }
    else {
        if (hzrd[vertex] == 1) {
            depth[vertex] = depth[par] + 1;
        }
        else {
            depth[vertex] = 0;
            if (depth[par] > m) depth[vertex] = -1;
        }
    }
    for (auto child : g[vertex]) {
        if (child == par) continue;
        dfs_ans(child, vertex);
        height[vertex] = max(height[vertex], height[child] + 1);
    }
}

void dfs(int vertex, int par = 0) {
    for (auto child : g[vertex]) {
        if (child == par) continue;
        dfs(child, vertex);
        height[vertex] = max(height[vertex], height[child] + 1);
    }
}


void reset() {
    for (int i = 0; i <= n; ++i) { // don't use N here, for every test case N (t*N might TLE)
        depth[i] = 0, height[i] = 0;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        hzrd[i] = x;
    }

    for (int i = 1; i <= n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);

    int point = n + 1;
    for (int i = 1; i <= n; ++i) {
        if (height[i] == 0) {
            // cout << i << ' ';
            g[i].push_back(point);
            g[point].push_back(i);
            point += 1;
        }
    }

    dfs_ans(1);

    int res = 0;
    for (int i = 1; i <= 2 * n; ++i) {
        cout << depth[i] << ' ';
        if (height[i] == 0  &&  depth[i] == -1) {
            res += 1;
        }
    }

    cout << res;

    return 0;
}

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> g[N];

vector<int> subtree_sum(N), val(N);

void dfs(int vertex, int par = -1) {
    subtree_sum[vertex] += val[vertex];
    for (auto child : g[vertex]) {
        if (child == par) continue;
        dfs(child, vertex); 
        subtree_sum[vertex] += subtree_sum[child];
    }
}


signed main() {
    int n;
    cin >> n;

    for (int i = 0; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    // root node 1 here
    dfs(1);

    long long ans = 0;
    for (int i = 2; i <= n; ++i) {
        int part1 = subtree_sum[i];
        int part2 = subtree_sum[1] - subtree_sum[i];
        ans = max(ans, (part1 * 1LL * part2));
    }

    cout << ans << '\n';
}
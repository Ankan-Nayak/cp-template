#include <bits/stdc++.h>
using namespace std;

/*
 BINARY LIFTING
 up[v][j] = the 2^j-th ancestor of v   (root's ancestors = root itself)
 Build:  O(N log N)    Query: O(log N)
 Gives: k-th ancestor, LCA, distance between two nodes.
 Nodes are 0..n-1.
*/
const int MAXN = 200005;
const int LOG  = 18;              // need 2^LOG > MAXN (2^18 = 262144)

int up[MAXN][LOG], dep[MAXN];
vector<int> g[MAXN];

void build(int root, int n) {
    // BFS, so every ancestor is processed before its descendants.
    // That guarantees up[x][j-1] is ready when we compute up[v][j].
    dep[root] = 0;
    up[root][0] = root;           // root's parent = itself (avoids -1 checks)
    queue<int> q;
    q.push(root);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int j = 1; j < LOG; j++)                   // 2^j ancestor = 2^(j-1) ancestor of the 2^(j-1) ancestor
            up[v][j] = up[ up[v][j-1] ][j-1];
        for (int u : g[v]) {
            if (u == up[v][0]) continue;                // skip parent
            dep[u] = dep[v] + 1;
            up[u][0] = v;
            q.push(u);
        }
    }
}

// k-th ancestor of v, returns -1 if it doesn't exist
int kth(int v, int k) {
    if (k > dep[v]) return -1;
    for (int j = 0; j < LOG; j++)
        if (k >> j & 1) v = up[v][j];                   // jump by each set bit of k
    return v;
}

int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    a = kth(a, dep[a] - dep[b]);                        // 1) lift deeper node to same depth
    if (a == b) return a;
    for (int j = LOG - 1; j >= 0; j--)                  // 2) lift both as high as possible
        if (up[a][j] != up[b][j])                       //    while they stay different
            a = up[a][j], b = up[b][j];
    return up[a][0];                                    // 3) parent of either = LCA
}

int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }

/*
 EXTENSION (path max/min/sum of edge weights):
 keep mx[v][j] = max edge weight on the 2^j steps above v:
   mx[v][0] = w(v, parent);  mx[v][j] = max(mx[v][j-1], mx[ up[v][j-1] ][j-1]);
 While lifting in kth()/lca(), also do ans = max(ans, mx[v][j]) before v = up[v][j].
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; a--; b--;
        g[a].push_back(b); g[b].push_back(a);
    }
    build(0, n);
    while (q--) {
        int a, b; cin >> a >> b; a--; b--;
        cout << lca(a, b) + 1 << "\n";
    }
}
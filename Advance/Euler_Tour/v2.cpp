#include <bits/stdc++.h>
using namespace std;

/*
 FULL EULER TOUR (size 2n-1)
 Write v on entering it AND again after returning from each child.
 first[v] = first index of v in euler[].
 LCA(u,v) = node with MINIMUM depth in euler[ first[u] .. first[v] ]  (swap if needed).
 Why: walking from u to v in the tour, the shallowest node you touch is their LCA.
 Build: O(N log N).  Query: O(1) with a sparse table.
*/
const int MAXN = 200005;
const int LG = 20;                          // 2^19 > 2*MAXN
vector<int> g[MAXN];
int par[MAXN], dep[MAXN], first_[MAXN];
vector<int> euler;
int sp[LG][2 * MAXN];                       // sparse table storing the NODE with min depth
int lg2[2 * MAXN];

int better(int a, int b) { return dep[a] < dep[b] ? a : b; }

void build(int root, int n) {
    vector<int> it(n, 0), st;
    par[root] = -1; dep[root] = 0;
    first_[root] = 0; euler.push_back(root);
    st.push_back(root);
    while (!st.empty()) {
        int v = st.back();
        if (it[v] < (int)g[v].size()) {
            int u = g[v][it[v]++];
            if (u == par[v]) continue;
            par[u] = v; dep[u] = dep[v] + 1;
            first_[u] = euler.size();
            euler.push_back(u);             // entering u
            st.push_back(u);
        } else {
            st.pop_back();
            if (!st.empty()) euler.push_back(st.back());   // back at parent
        }
    }
    int m = euler.size();
    lg2[1] = 0;
    for (int i = 2; i <= m; i++) lg2[i] = lg2[i / 2] + 1;
    for (int i = 0; i < m; i++) sp[0][i] = euler[i];
    for (int j = 1; (1 << j) <= m; j++)
        for (int i = 0; i + (1 << j) <= m; i++)
            sp[j][i] = better(sp[j-1][i], sp[j-1][i + (1 << (j-1))]);
}

int lca(int u, int v) {
    int l = first_[u], r = first_[v];
    if (l > r) swap(l, r);
    int j = lg2[r - l + 1];
    return better(sp[j][l], sp[j][r - (1 << j) + 1]);   // two overlapping blocks cover [l, r]
}
int dist(int u, int v) { return dep[u] + dep[v] - 2 * dep[lca(u, v)]; }

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        g[u].push_back(v); g[v].push_back(u);
    }
    build(0, n);
    while (q--) {
        int u, v; cin >> u >> v; u--; v--;
        cout << lca(u, v) + 1 << "\n";
    }
}
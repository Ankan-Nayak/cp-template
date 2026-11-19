#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
 EULER TOUR (tin/tout)
 tin[v]  = time when we first enter v          (0..n-1)
 tout[v] = tin of the LAST node in v's subtree (inclusive)
 => subtree of v = positions [tin[v], tout[v]] in the order[] array.
 => u is ancestor of v  <=>  tin[u] <= tin[v] && tin[v] <= tout[u]
 Build: O(N).  Turns subtree problems into range problems (BIT / segtree).
*/
const int MAXN = 200005;
vector<int> g[MAXN];
int tin[MAXN], tout[MAXN], par[MAXN], dep[MAXN], ord_[MAXN], timer_ = 0;

void dfs(int root) {
    vector<int> it(MAXN, 0), st;           // it[v] = next child index to explore
    par[root] = -1; dep[root] = 0;
    st.push_back(root);
    tin[root] = timer_; ord_[timer_++] = root;
    while (!st.empty()) {
        int v = st.back();
        if (it[v] < (int)g[v].size()) {
            int u = g[v][it[v]++];
            if (u == par[v]) continue;     // skip parent
            par[u] = v; dep[u] = dep[v] + 1;
            tin[u] = timer_; ord_[timer_++] = u;   // entering u
            st.push_back(u);
        } else {
            tout[v] = timer_ - 1;          // leaving v: everything visited so far is in its subtree
            st.pop_back();
        }
    }
}

bool isAnc(int u, int v) { return tin[u] <= tin[v] && tin[v] <= tout[u]; }

/* ---------- Fenwick tree (point update, prefix sum) ---------- */
struct BIT {
    int n; vector<ll> t;
    void init(int n_) { n = n_; t.assign(n + 1, 0); }
    void add(int i, ll v) { for (i++; i <= n; i += i & -i) t[i] += v; }   // a[i] += v
    ll pre(int i) { ll s = 0; for (i++; i > 0; i -= i & -i) s += t[i]; return s; } // sum a[0..i]
    ll range(int l, int r) { return pre(r) - (l ? pre(l - 1) : 0); }
};

/*
 TYPICAL USES
 (a) Subtree sum + point update:
       bit.add(tin[v], x);  ans = bit.range(tin[v], tout[v]);
 (b) Add x to every node in subtree of v, query value of single node u:
       bit.add(tin[v], x); bit.add(tout[v] + 1, -x);   // difference array
       ans = bit.pre(tin[u]);
 (c) Point update at v, sum of root->u path (this is the "dual" of (a)):
       bit.add(tin[v], x); bit.add(tout[v] + 1, -x);   // v's value counts for all nodes under it
       ans = bit.pre(tin[u]);                          // = sum of values on path root..u
 Note: when tout[v]+1 == n, add() is harmless only if BIT size is n+1, so init(n + 1).
*/

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        g[u].push_back(v); g[v].push_back(u);
    }
    dfs(0);
    BIT bit; bit.init(n + 1);
    for (int v = 0; v < n; v++) bit.add(tin[v], a[v]);
    while (q--) {
        int t; cin >> t;
        if (t == 1) { int v; ll x; cin >> v >> x; v--; bit.add(tin[v], x - a[v]); a[v] = x; }  // set value
        else        { int v; cin >> v; v--; cout << bit.range(tin[v], tout[v]) << "\n"; }       // subtree sum
    }
}
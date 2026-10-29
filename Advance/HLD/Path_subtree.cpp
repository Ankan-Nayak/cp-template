#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/*
 LAZY SEGMENT TREE: range add, range sum. 0-indexed, inclusive [l, r].
 Point update = range add on [i, i]. To change to max/min, edit apply/pull/query.
*/
struct SegTree {
    int n; vector<ll> t, lz;
    void init(const vector<ll>& a) {
        n = a.size(); t.assign(4*n, 0); lz.assign(4*n, 0);
        build(1, 0, n-1, a);
    }
    void build(int x, int l, int r, const vector<ll>& a) {
        if (l == r) { t[x] = a[l]; return; }
        int m = (l + r) / 2;
        build(2*x, l, m, a); build(2*x+1, m+1, r, a);
        t[x] = t[2*x] + t[2*x+1];
    }
    void app(int x, int l, int r, ll v) { t[x] += v * (r - l + 1); lz[x] += v; }
    void push(int x, int l, int r) {
        if (!lz[x]) return;
        int m = (l + r) / 2;
        app(2*x, l, m, lz[x]); app(2*x+1, m+1, r, lz[x]);
        lz[x] = 0;
    }
    void update(int x, int l, int r, int ql, int qr, ll v) {
        if (qr < l || r < ql) return;
        if (ql <= l && r <= qr) { app(x, l, r, v); return; }
        push(x, l, r);
        int m = (l + r) / 2;
        update(2*x, l, m, ql, qr, v); update(2*x+1, m+1, r, ql, qr, v);
        t[x] = t[2*x] + t[2*x+1];
    }
    ll query(int x, int l, int r, int ql, int qr) {
        if (qr < l || r < ql) return 0;
        if (ql <= l && r <= qr) return t[x];
        push(x, l, r);
        int m = (l + r) / 2;
        return query(2*x, l, m, ql, qr) + query(2*x+1, m+1, r, ql, qr);
    }
    void update(int l, int r, ll v) { update(1, 0, n-1, l, r, v); }
    ll   query(int l, int r)        { return query(1, 0, n-1, l, r); }
};

/*
 HEAVY-LIGHT DECOMPOSITION
 Idea: heavy child = child with the biggest subtree. Heavy edges form chains.
 Any root-to-node path crosses at most O(log N) light edges, so it splits into
 O(log N) chain segments. Chains are laid out contiguously in an array
 (pos[]), so each segment is a range query on a segment tree.
 Total: O(log^2 N) per path query/update, O(log N) for subtree ones.

 DFS order visits the heavy child FIRST, which gives two properties:
   1) every chain is contiguous in pos[]
   2) subtree of v = [pos[v], pos[v] + sz[v] - 1]
*/
struct HLD {
    int n, timer = 0;
    vector<vector<int>> g;
    vector<int> par, dep, sz, heavy, head, pos;
    SegTree st;

    HLD(int n) : n(n), g(n), par(n, -1), dep(n), sz(n, 1),
                 heavy(n, -1), head(n), pos(n) {}

    void addEdge(int u, int v) { g[u].push_back(v); g[v].push_back(u); }

    // vals[v] = initial value on vertex v
    void build(const vector<ll>& vals, int root = 0) {
        // Pass 1: iterative DFS to get parent, depth and a preorder
        vector<int> order; order.reserve(n);
        vector<int> stk = {root};
        par[root] = -1; dep[root] = 0;
        while (!stk.empty()) {
            int v = stk.back(); stk.pop_back();
            order.push_back(v);
            for (int u : g[v]) if (u != par[v]) {
                par[u] = v; dep[u] = dep[v] + 1; stk.push_back(u);
            }
        }
        // Pass 2: reverse preorder = children before parents -> subtree sizes + heavy child
        for (int i = n - 1; i > 0; i--) {
            int v = order[i], p = par[v];
            sz[p] += sz[v];
        }
        for (int i = n - 1; i > 0; i--) {
            int v = order[i], p = par[v];
            if (heavy[p] == -1 || sz[v] > sz[heavy[p]]) heavy[p] = v;
        }
        // Pass 3: assign pos[] with a DFS that visits the heavy child first.
        // Push light children first and heavy child LAST so it is popped next.
        head[root] = root;
        stk = {root};
        while (!stk.empty()) {
            int v = stk.back(); stk.pop_back();
            pos[v] = timer++;
            for (int u : g[v]) if (u != par[v] && u != heavy[v]) {
                head[u] = u;                     // light child starts a new chain
                stk.push_back(u);
            }
            if (heavy[v] != -1) {
                head[heavy[v]] = head[v];        // heavy child continues the chain
                stk.push_back(heavy[v]);
            }
        }
        vector<ll> base(n);
        for (int v = 0; v < n; v++) base[pos[v]] = vals[v];
        st.init(base);
    }

    // Calls f(l, r) for every segment of the path u..v (positions, inclusive).
    // edges=true -> values stored on edges (value of edge = value of child vertex),
    // so the LCA itself is excluded.
    template <class F>
    void path(int u, int v, F f, bool edges = false) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);   // move the one whose chain head is deeper
            f(pos[head[u]], pos[u]);
            u = par[head[u]];                              // jump over the light edge
        }
        if (dep[u] > dep[v]) swap(u, v);                   // same chain now: u is the shallower
        f(pos[u] + (edges ? 1 : 0), pos[v]);
    }
    // NOTE: for non-commutative operations (e.g. string concat) you must also
    // track the direction of each segment; sum/max/min/xor are fine as is.

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) swap(u, v);
            u = par[head[u]];
        }
        return dep[u] < dep[v] ? u : v;
    }

    // ---- ready-made operations (vertex values) ----
    ll queryPath(int u, int v) {
        ll res = 0;
        path(u, v, [&](int l, int r) { res += st.query(l, r); });
        return res;
    }
    void updatePath(int u, int v, ll x) {                  // add x to every vertex on path
        path(u, v, [&](int l, int r) { st.update(l, r, x); });
    }
    ll querySubtree(int v)        { return st.query(pos[v], pos[v] + sz[v] - 1); }
    void updateSubtree(int v, ll x) { st.update(pos[v], pos[v] + sz[v] - 1, x); }
    void updateVertex(int v, ll x)  { st.update(pos[v], pos[v], x); }  // adds x
};

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<ll> a(n);
    for (auto& x : a) cin >> x;
    HLD h(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v; u--; v--;
        h.addEdge(u, v);
    }
    h.build(a, 0);
    while (q--) {
        int t; cin >> t;
        if (t == 1) { int v; ll x; cin >> v >> x; v--; h.updateVertex(v, x); }
        else        { int u, v; cin >> u >> v; u--; v--; cout << h.queryPath(u, v) << "\n"; }
    }
}
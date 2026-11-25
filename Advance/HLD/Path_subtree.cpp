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

/*
=========================================================
HLD (Heavy-Light Decomposition): picture of chains

Legend:  ||  = heavy edge (same chain)
         /,\ = light edge (a new chain starts below it)
         [p] = position in the segment tree / base array
         (s) = subtree size

                      1 [0] (10)
                     /  \
               ||---/      \---\
              2 [1] (6)       3 [7] (3)
             /  \                ||
          ||/    \             6 [8] (2)
          4 [2]   5 [5] (2)      ||
          (3)       ||         9 [9] (1)
         /  \     10 [6] (1)
      ||/    \
     7 [3]   8 [4]
     (1)     (1)

Heavy child = child with the largest subtree size.
(Tie at node 4: 7 and 8 both have size 1, so the first one, 7, is chosen.)

CHAINS (head -> down):
  Chain A: 1 -> 2 -> 4 -> 7     head = 1, positions 0,1,2,3
  Chain B: 8                    head = 8, position  4
  Chain C: 5 -> 10              head = 5, positions 5,6
  Chain D: 3 -> 6 -> 9          head = 3, positions 7,8,9

Each chain gets CONTIGUOUS positions, so one chain = one
segment tree range. Positions come from a DFS that visits
the heavy child FIRST.

base array index:  0  1  2  3  4  5  6  7  8  9
node at index:     1  2  4  7  8  5  10 3  6  9
chain head:        1  1  1  1  8  5  5  3  3  3

PATH QUERY EXAMPLE: path(9, 7)
  u = 9, v = 7
  head[9] = 3, head[7] = 1   (different chains)
  step 1: depth[head[9]=3] > depth[head[7]=1] -> lift u
          query range [pos[3], pos[9]] = [7, 9]
          u = parent[3] = 1
  step 2: head[1] = 1, head[7] = 1 (same chain)
          query range [pos[1], pos[7]] = [0, 3]
  Total: 2 segment tree range queries, combine the results.
  Any path has at most O(log n) light edges, so O(log n) chains,
  so O(log^2 n) per query.
=========================================================
*/
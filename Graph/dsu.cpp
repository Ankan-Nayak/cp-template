#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
int parent[N];
int sz[N];

void make(int v) {
    parent[v] = v;
    sz[v] = 1;
}

int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (sz[a] < sz[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        make(i);
    }   
    
    while(k--) {
        int u, v;
        cin >> u >> v;
        Union(u, v);
    }

    int connected_ct = 0;
    for (int i = 1; i <= n; ++i) {
        if (find(i) == i) connected_ct += 1;
    }
    cout << connected_ct;

    return 0;
}

// 𝑂(𝛼(𝑛)) per query = O(4) at max






//another approach class
class UnionFind
{
private:
    vector<int> par;
    vector<int> sz;

public:
    UnionFind(int n)
    {
        par = vector<int>(n);
        iota(par.begin(), par.end(), 0);
        sz = vector<int>(n, 1);
    }

    int find(int u)
    {
        // this optimisation was good.
        if (par[u] != par[par[u]])
            par[u] = find(par[par[u]]);
        return par[u];
    }

    bool connected(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
            return true;
        return false;
    }

    bool join(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
            return false;
        if (sz[u] <= sz[v])
        {
            sz[v] += sz[u];
            par[u] = v;
        }
        else
        {
            sz[u] += sz[v];
            par[v] = u;
        }
        return true;
    }
};
// call UnionFind uf1(n), uf2(n);


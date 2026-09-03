#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e5;
int parent[N];
int sz[N];

multiset<int> sizes;

void make(int v) {
    parent[v] = v;
    sz[v] = 1;
    sizes.insert(1);
} 

void merge(int a, int b) {
    sizes.erase(sizes.find(sz[a]));
    sizes.erase(sizes.find(sz[b]));

    sizes.insert(sz[a] + sz[b]);
}

int find(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find(parent[v]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (sz[a] < sz[b]) {
            swap(a, b);
        }
        parent[b] = a;
        merge(a, b);
        sz[a] += sz[b];
    }
}

signed main() 
{
    int n, k;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        make(i);
    }

    while (k--) {
        int u, v;
        cin >> u >> v;
        Union(u, v);
        if (sizes.size() == 1) {
            cout << 0 << endl; 
        } else {
            cout << *(sizes.rbegin()) - *(sizes.begin()) << endl;
        }
    }

    int ct = 0;
    for (int i = 1; i <= n; ++i) {
        if (find(i) == i) {
            ct += 1;
        }
    }

    cout << ct;
    
    
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


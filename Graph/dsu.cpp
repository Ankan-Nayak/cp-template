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


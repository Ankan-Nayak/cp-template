#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 2e3+10;
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

    int n;
    cin >> n;
    vector<pair<int, int>> cities(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> cities[i].first >> cities[i].second;
    }

    vector<int> c(n+1), k(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
    }

    vector<pair<int, pair<int, int>>> edges;
    
    int new_node = 0;
    for (int i = 1; i <= n; ++i) {
        edges.push_back({c[i], {new_node, i}});
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            int dist = abs(cities[i].first - cities[j].first) + abs(cities[i].second - cities[j].second);
            int cost = (k[i] + k[j]) * 1LL * dist;
            edges.push_back({cost, {i, j}});
        }
    }


    sort(edges.begin(), edges.end());

    for (int i = 0; i <= n; ++i) make(i);

    int total_cost = 0;
    vector<int> power_station;
    vector<pair<int, int>> connections;
    for (auto &edge : edges) {
        int wt = edge.first;
        int u = edge.second.first, v = edge.second.second;
        if (find(u) == find(v)) continue;
        Union(u, v);
        total_cost += wt;
        if (u == 0  || v == 0) power_station.push_back(max(u, v)); 
        else connections.push_back({u, v});
    }

    
    cout << total_cost << '\n';
    cout << power_station.size() << '\n';
    for (auto station : power_station) {
        cout << station << ' ';
    }

    cout << '\n' << connections.size() << '\n';
    for (auto connection : connections) {
        cout << connection.first << ' ' << connection.second << '\n';
    }

    return 0;
}









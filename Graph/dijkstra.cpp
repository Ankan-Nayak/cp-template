#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
const int inf = 1e9+10;

vector<int> vis(N, 0);
vector<int> dist(N, inf);

// node, wt
vector<pair<int, int>> g[N];

void dijkstra(int source) {
    // wt, node
    set<pair<int, int>> st;
    st.insert({0, source});
    dist[source] = 0;
    while (st.size() > 0) {
        auto node = *st.begin();
        int v = node.second;
        int v_dist = node.first;
        st.erase(st.begin());
        if (vis[v] == 1) continue;
        vis[v] = 1;
        for (auto child : g[v]) {
            int child_v = child.first;
            int wt = child.second;
            if (dist[v] + wt < dist[child_v]) {
                dist[child_v] = dist[v] + wt;
                st.insert({dist[child_v], child_v});
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y, wt;
        cin >> x >> y >> wt;
        g[x].push_back({y, wt}); // directed graph
        // g[y].push_back({x, wt});  if it's undirected graph
    }

    int source, destination;
    cin >> source >> destination;
    dijkstra(source);

    cout << dist[destination];

    return 0;
}

// O((n+m)logn)

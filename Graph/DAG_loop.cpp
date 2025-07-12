void dfs(int u) {
    state[u] = 1;
    for (int v : adj[u]) {
        if (state[v] == 1) {
            cycle = true;
            return;
        }
        if (state[v] == 0) {
            dfs(v);
        }

        if (cycle) return;
    }
    state[u] = 2;
}





#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> g;
vector<int> col;
vector<int> parent;
vector<int> depth;

bool is_cycle = 0;
vector<int> any_cycle;

void dfs(int node, int par) {
    parent[node] = par;
    col[node] = 2;

    for (auto v : g[node]) {
        // if (v == par) continue;  for undirected graph
        if (col[v] == 1) {
            depth[v] = depth[node] + 1;
            // node -> v is a forward edge
            dfs(v, node);
        } else if (col[v] == 2) {
            // node -> v is a back edge
            // We found a cycle !!
            if (is_cycle == 0) {
                int temp = node;
                while (temp != v) {
                    // int cycle_length = depth[node] - depth[v] + 1;
                    // if (cycle_length % 2 == 1) {
                    //     is_cycle = 1;
                    //     return;
                    // }
                    any_cycle.push_back(temp);
                    temp = parent[temp];
                }
                any_cycle.push_back(v);
                reverse(any_cycle.begin(), any_cycle.end()); // Optional: for ordered cycle
            }
            is_cycle = 1;
        } else if (col[v] == 3) {
            // Cross edge (in DAGs this doesn't appear, but safe to ignore)
            continue;
        }
    }

    col[node] = 3;
}

int main() {
    int n, m;
    cin >> n >> m;

    g.resize(n + 1);
    col.assign(n + 1, 1);      // all nodes initially unvisited
    parent.assign(n + 1, -1);  // initialize parent as -1
    depth.resize(n + 1);


    map<pair<int, int>, int> edgecnt;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;

        // if (u > v) swap(u, v);
        // edgecnt[{u, v}]++;
        // if (edgecnt[{u, v}] > 1) {
        //     // multiple edge cycle
        // } else {

        
            // if (u == v) {
            //     // self loop
            // }
            g[u].push_back(v); // Directed graph
            // g[v].push_back(u);
        // }
    }

    for (int i = 1; i <= n; ++i) {
        if (col[i] == 1) {
            dfs(i, -1);
            if (is_cycle) break;
        }
    }

    if (is_cycle) {
        cout << "Cycle found:\n";
        for (int node : any_cycle) {
            cout << node << " ";
        }
        cout << '\n';
    } else {
        cout << "No cycle found\n";
    }

    return 0;
}

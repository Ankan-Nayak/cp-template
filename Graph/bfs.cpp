#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
vector<int> g[N];

int vis[N];
int level[N];
vector<int> parent(N, -1);

vector<int> get_path(int target) {
    vector<int> path;
    for (int v = target; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}


void bfs(int source) {
    queue<int> q;
    q.push(source);
    vis[source] = 1;

    while(!q.empty()) {
        int curr_v = q.front();
        q.pop();
        for (int child : g[curr_v]) {
            if (!vis[child]) {
                q.push(child);
                vis[child] = 1;
                level[child] = level[curr_v] + 1;
                parent[child] = curr_v;
            }
        }
    }
}


signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    bfs(1);

    for (int i = 1; i <= n; ++i) {
        cout << level[i] << ' ';
    }
}

// give shortest path from root for equal weighted edges
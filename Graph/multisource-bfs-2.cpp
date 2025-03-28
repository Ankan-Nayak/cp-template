#include <bits/stdc++.h>
using namespace std;

const int N = 1e3+10;
const int inf = 1e9+10;

int val[N][N];
int vis[N][N];
int lev[N][N];

vector<pair<int, int>> movements {
    {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
};

bool isValid(int i, int j) {
    return i >= 0  &&  j >= 0  &&  i < n  &&  j < m;
}

int n, m;

int bfs() {
    int mx = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mx = max(mx, val[i][j]);
        }
    }

    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            // using all max values as source
            if (mx == val[i][j]) {
                q.push({i, j});
                lev[i][j] = 0;
                vis[i][j] = 1;
            }
        }
    }

    int ans = 0;
    while (!q.empty()) {
        auto v = q.front();
        int v_x = v.first;
        int v_y = v.second;
        q.pop();

        for (auto movement : movements) {
            int child_x = movement.first + v_x;
            int child_y = movement.second + v_y;
            if (!isValid(child_x, child_y)) continue;
            if (vis[child_x][child_y]) continue;
            q.push({child_x, child_y});
            lev[child_x][child_y] = lev[v_x][v_y] + 1;
            vis[child_x][child_y] = 1;
            ans = max(ans, lev[child_x][child_y]);
        }
    }
    return ans;
}

void reset() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            vis[i][j] = 0;
            lev[i][j] = inf;
        }
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> val[i][j];
        }
    }

    cout << bfs();
}

question
 - A graph given, some sources given, min distance to reach the the destination node first

solution
 - just put all source in queue 
 - run normal bfs
 - at a time there's 2 level possible in queue
 - whatever node reach destination first, the level will be min
 
 #include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
int n, m; // Grid dimensions
vector<vector<int>> grid;
vector<pair<int, int>> start, end;

int main() {
    // Input grid size
    cin >> n >> m;

    // Read the grid
    grid.assign(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> grid[i][j]; // 0 = free, 1 = blocked

    // Input source points
    int ns;
    cin >> ns;
    for (int i = 0; i < ns; i++) {
        int sx, sy;
        cin >> sx >> sy;
        start.push_back({sx, sy});
    }

    // Input destination points
    int ne;
    cin >> ne;
    for (int i = 0; i < ne; i++) {
        int ex, ey;
        cin >> ex >> ey;
        end.push_back({ex, ey});
    }

    // Direction arrays
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    vector<vector<int>> dist(n, vector<int>(m, -1));
    queue<pair<int, int>> q;

    // Initialize BFS with all start points
    for (auto S : start) {
        int sx = S.first;
        int sy = S.second;
        q.push({sx, sy});
        dist[sx][sy] = 0;
    }

    // BFS loop
    while (!q.empty()) {
        auto it = q.front(); q.pop();
        int curx = it.first;
        int cury = it.second;

        for (int i = 0; i < 4; i++) {
            int neighx = curx + dx[i];
            int neighy = cury + dy[i];

            if (neighx >= 0 && neighx < n && neighy >= 0 && neighy < m) {
                if (!grid[neighx][neighy]) {
                    if (dist[neighx][neighy] == -1) {
                        dist[neighx][neighy] = dist[curx][cury] + 1;
                        q.push({neighx, neighy});
                    }
                }
            }
        }
    }

    // Find the minimum distance to any of the end points
    int ans = INF;
    for (auto E : end) {
        int ex = E.first;
        int ey = E.second;
        if (dist[ex][ey] != -1) {
            ans = min(ans, dist[ex][ey]);
        }
    }

    if (ans == INF) cout << -1 << endl; // No path found
    else cout << ans << endl;

    return 0;
}

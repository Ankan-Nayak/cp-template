// 1. dfs approach

#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int n, m, q;

void dfs(vector<vector<int>> &grid, int x, int y, int &white_cell) {
    // Mark current cell as black and decrease white count
    grid[x][y] = 0;
    white_cell--;
    
    // Explore all 4 neighbors
    for (int d = 0; d < 4; ++d) {
        int nx = x + dx[d];
        int ny = y + dy[d];  // Fixed: was dx[d] instead of dy[d]
        
        // Check bounds and if it's a white cell
        if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == 1) {
            dfs(grid, nx, ny, white_cell);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    // Removed test case loop - problem doesn't mention multiple test cases
    cin >> n >> m >> q;
    
    int white_cell = 0;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) white_cell++;
        }
    }
    
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--; y--;  // Convert to 0-based indexing
        
        // Check if click is valid and on a white cell
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == 0) {
            cout << white_cell << '\n';
        } else {
            dfs(grid, x, y, white_cell);
            cout << white_cell << '\n';
        }
    }
    
    return 0;
}




// 2. bfs approach

#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int n, m, q;

void bfs(vector<vector<int>> &grid, int x, int y, int &white_cell) {
    queue<pair<int, int>> que;  // Changed variable name to avoid conflict
    que.push({x, y});

    grid[x][y] = 0;
    white_cell--;
    
    while (!que.empty()) {
        pair<int, int> curr = que.front();
        que.pop();
        
        int cx = curr.first;
        int cy = curr.second;
        
        for (int d = 0; d < 4; d++) {
            int nx = cx + dx[d];
            int ny = cy + dy[d];

            if (nx >= 0 && ny >= 0 && nx < n && ny < m && grid[nx][ny] == 1) {
                grid[nx][ny] = 0;
                white_cell--;
                que.push({nx, ny});
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> m >> q;
    
    int white_cell = 0;
    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) white_cell++;
        }
    }
    
    int queries = q;  // Store the number of queries in a separate variable
    while (queries--) {
        int x, y;
        cin >> x >> y;
        x--; y--;  
    
        if (x < 0 || x >= n || y < 0 || y >= m || grid[x][y] == 0) {
            cout << white_cell << '\n';
        } else {
            bfs(grid, x, y, white_cell);
            cout << white_cell << '\n';
        }
    }
    
    return 0;
}
class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int n = grid.size();
        int m = grid[0].size();
        int vis[n+2][m+2][k+2];
        memset(vis, 0, sizeof(vis));

        queue<array<int, 4>> q;
        q.push({0,0,0,0});
        vis[0][0][0] = 1;

        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        if (k >= n + m - 2) return n + m - 2;

        while (!q.empty()) {
            auto [i,j,K,step] = q.front();
            q.pop();

            if (i == n-1 && j == m-1) {
                return step;
            }

            for (int d = 0; d < 4; ++d) {
                int x = dx[d] + i;
                int y = dy[d] + j;

                if (x < 0 || x >= n || y < 0 || y >= m) {
                    continue;
                }

                int nk = K + grid[x][y];
                if (!vis[x][y][nk] && nk <= k) {
                    q.push({x,y,nk,step+1});
                    vis[x][y][nk] = 1;
                }
            }

        }
        return -1;
    }
};
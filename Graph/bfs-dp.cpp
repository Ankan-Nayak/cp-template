        vector<vector<int>> dist(n, vector<int>(2, inf));
 
        queue<pair<int, int>> q;
        q.push({0, 0});
        dist[0][0] = 0;
 
        while(!q.empty()) {
            auto [u, p] = q.front();
            q.pop();
            for (int child : g[u]) {
                if (dist[child][!p] > dist[u][p] + 1) {
                    dist[child][!p] = dist[u][p] + 1;
                    q.push({child, !p});
                }
                
            }
        }
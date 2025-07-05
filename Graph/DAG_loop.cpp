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
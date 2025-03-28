const int N = 1e5+10;
bool vis[N];
vector<int> g[N];
bool dfs(int vertex, int par = -1) {
    vis[vertex] = true;
    bool isLoopExists = false;
    for (auto child : g[vertex]) {
        if (vis[child]  &&  child == par) continue;
        if (vis[child]) return true;
        isLoopExists |= dfs(child, vertex);
    }
    return isLoopExists;
}

bool isLoopExists = false;
for (int i = 1; i <= n; ++i) {
    if (vis[i]) continue;
    if (dfs(i)) {
        isLoopExists = true;
        break;
    }
}

cout << isLoopExists << '\n';
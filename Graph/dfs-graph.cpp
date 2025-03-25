const int N = 1e5+10;
bool vis[N];
vector<int> g[N];
void dfs(int vertex) {
    // take action on vertex after entering the vertex
    vis[vertex] = true;
    for (auto child : g[vertex]) {
        if (vis[child]) continue;
        // take action on child before entering the child node
        dfs(child);
        // take action on child after entering the child node
    }
    // take action on vertex before entering the vertex
}
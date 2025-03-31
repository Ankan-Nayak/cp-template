
const int N = 1e5+10;
bool visited[N];
void dfs(int vertex, int par = -1) {
    visited[vertex] = true;  // mark as visited
    for (auto child : g[vertex]) {
        if (child == par || visited[child]) continue;
        dfs(child, vertex);
    }
}

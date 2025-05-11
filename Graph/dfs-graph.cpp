
const int N = 1e5+10;
bool visited[N];
void dfs(int vertex, int par = -1) {
    visited[vertex] = true;  // mark as visited
    for (auto child : g[vertex]) {
        if (child == par || visited[child]) continue;
        dfs(child, vertex);
    }
}

// unordered_map<int, unordered_map<int, int>> mp;
// mp[1e9][1e9] = 1e9
// for adjancy matrix
// inf size 2d matrix

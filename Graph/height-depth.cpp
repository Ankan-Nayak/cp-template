const int N = 1e5+10;
bool vis[N];
vector<int> g[N];

int height[N], depth[N];

void dfs(int vertex, int par = -1) {
    for (auto child : g[vertex]) {
        if (child == par) continue;
        depth[child] = depth[vertex] + 1;
        dfs(child, vertex);
        height[vertex] = max(height[vertex], height[child] + 1);
    }
}

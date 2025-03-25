const int N = 1e5+10;
bool vis[N];
vector<int> g[N];

vector<vector<int>> connected_components;
vector<int> current_connected_component;

void dfs(int vertex) {
    vis[vertex] = true;
    current_connected_component.push_back(vertex);
    for (auto child : g[vertex]) {
        if (!vis[child])
            dfs(child);
    }
}

int ct = 0;
for (int i = 1; i <= n; ++i) {
    if (vis[i]) continue;
    current_connected_component.clear();
    dfs(i);
    connected_components.push_back(current_connected_component);
    ct++;
}

cout << ct << '\n';
for (auto component : connected_components) {
    for (int vertex : component) {
        cout << vertex << ' ';
    }
    cout << '\n';
}

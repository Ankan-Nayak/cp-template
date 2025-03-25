const int N = 1e5+10;
bool vis[N];
vector<int> g[N];

int height[N], depth[N];
vector<int> subtree_sum(N), even_cnt(N), val(N);

void dfs(int vertex, int par = -1) {
    subtree_sum[vertex] += val[vertex];
    if (val[vertex] % 2 == 0) 
        even_cnt[vertex] += 1;
    for (auto child : g[vertex]) {
        if (child == par) 
            continue;
        dfs(child, vertex); 
        subtree_sum[vertex] += subtree_sum[child];
        even_cnt[vertex] += even_cnt[child];
    }
}

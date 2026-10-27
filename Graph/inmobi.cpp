#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 1e6;
vector<int> g[N];
bool vis[N];

int ct = 0;

bool visited[N];
                  // start at 0, not 1

int dfs(int v, int par = -1) {    // returns 1 if v's path is still open
    int open = 0;
    for (int c : g[v]) {
        if (c == par) continue;
        open += dfs(c, v);
    }
    if (open == 0) { ct++; return 1; }   // leaf: start a new path
    if (open == 1) return 1;             // extend the child's path
    ct--; return 0;                      // join two child paths, now closed
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int root = -1;

    for (int i = 1; i <= n; ++i) {
        if (g[i].size() == 1) {
            root = i;
            break;
        }
    }

    if (root == -1) root = 1;

    dfs(root);

    cout << ct << endl;

    return 0;
}
/*
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */

 /*
 Minimum Paths to Cover a Tree

Given a tree with N nodes (labelled 1..N) and N-1 edges, cover all nodes
using paths along edges such that every node belongs to exactly one path
(no node is visited more than once overall).
Find the minimum number of paths needed.

Input:
  N
  N-1 lines: u v   (an edge between u and v)

Output:
  A single integer: the minimum number of paths.

Constraints:
  1 <= N <= 10^5

Example:
  Input:
    6
    1 2
    2 3
    3 4
    2 5
    3 6
  Output:
    2
  Explanation: paths 1-2-5 and 4-3-6
  */
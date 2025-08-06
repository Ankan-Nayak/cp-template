#include <bits/stdc++.h>
using namespace std;

const int N = 1e5+10;
bool vis[N];
vector<int> g[N];

int depth[N];

void dfs(int vertex, int par = -1) {
    for (auto child : g[vertex]) {
        if (child == par) continue;
        depth[child] = depth[vertex] + 1;
        dfs(child, vertex); 
    }
}


signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    // root node 1 here
    dfs(1);

    int mx_depth = -1;
    int mx_depth_node;
    for (int i = 1; i <= n; ++i) {
        if (mx_depth <depth[i]) {
            mx_depth = depth[i];
            mx_depth_node = i;
        }
        // reset
        depth[i] = 0;
    }

    dfs(mx_depth_node);

    for (int i = 1; i <= n; ++i) {
        if (mx_depth <depth[i]) {
            mx_depth = depth[i];
            mx_depth_node = i;
        }
    }

    cout << mx_depth << '\n';
}

















// CF(1023 - div2) -> Apple Tree Traversing -> Teja-Smart



#include<bits/stdc++.h>
using namespace std;
#define int long long

// Problem Statement
/*
    
*/
 
// Small Observatins
/*
    we choose a path u, v on a tree of length d

        we write (d, u, v) on paper


        d1, u1, v1, d2, u2, v2 ..... 




        So, at any points
            we have some subtrees

            OK
                let l be the maximum diameter of all these subtrees !!

                Now, what we do in one step, we will find maximum diameter of all these subtrees and remove that

                The maximum diameter among smaller trees must REDUCE !!


                if l <= root(n)
                    we can above step that takes O(n) complexiry
                    but we do that atmax l times
                    n root(n)
                
                if l  >= root(n)
                    we remove diameter, we remove l elements

                    How many times at max u can do such things !! 
                        root(n)

                        total number of elements itself <= n

                        if u keep removing l things >= root(n)

                        u can to z times
                            z * l <= n
                            z <= root(n)


    S = {}

    Repeat 
        Take a subtree : 
            find its best (d, u, v)
                add (d, u, v) to S
                reomve thiis path
    

    sort(S)
    output(S)

    nroot(n)


    
    Once, I remove a vertex, should I remove it from edges of remainting vertices

        Or I can just mark that vertex as removed and not explore it !!

        If you dont remove that edge. OK 
            to v
            u may approach this edge, u may touch this edge
                at max 2 root(n) times. 

                m root(n), n root(n)



    In finding diamater, 
        we use somethnig like
            finding the farthest leaf.
    

        Now we need,
            given a vertex v, 
                find its farthest , largest node : )

        
            If we have this, 

            we can take some vertex, find best vertex on one side

            now take that vertex , find best on the other side

*/

 
 
 
/*

*/
 
 
// Claims on algo 
/*  
    
 
*/


#define N 150010

vector<int> adj[N];

int removed[N], parent[N];

int len = -1, val = 0;
void dfs(int v, int p, int h){
    parent[v] = p;
    if (h > len){
        len = h;
        val = v;
    }
    else if (h == len && v > val){
        val = v;
    }

    for (int u : adj[v]){
        if (u != p && !removed[u]){
            dfs(u, v, h + 1);
        }
    }
}


void solve(){
    int n; cin >> n;
    for (int i = 0; i <= n; i++){
        adj[i].clear();
        removed[i] = 0;
    }

    for (int i = 0; i < n - 1; i++){
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<vector<int>> ans;
    for (int i = 1; i <= n; i++){
        while (!removed[i]){
            len = -1, val = 0;
            dfs(i, i, 0);
            int u = val;
            len = -1, val = 0;
            dfs(u, u, 0);
            int v = val, d = len + 1;
            // remove the path from v to u
            int x = v;
            while (x != u){
                removed[x] = 1;
                x = parent[x];
            }
            removed[u] = 1;
            if (u < v) swap(u, v);
            ans.push_back({-d, -u, -v});
            // we should now go over parents of v, until u and mark them as removed
            // So we found already a good and must be present candidate in the sequence
        }
    }
    sort(ans.begin(), ans.end());
    for (auto f : ans) cout << -f[0] << ' ' << -f[1] << ' ' << -f[2] << ' ';
    cout << '\n';
}

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
 
    int t; cin >> t;
    while (t--) solve();
}
 
// Golden Rules
/*
    Solutions are simple.
 
    Proofs are simple.
 
    Implementations are simple.
*/

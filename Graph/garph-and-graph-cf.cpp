#include<bits/stdc++.h>
using namespace std;

#define int long long
const int inf = 1e9+7;

void solve () {
    int n, s1, s2;
    cin >> n >> s1 >> s2;
    int m1;
    cin >> m1;
    vector<pair<int, int>> a1;
    set<pair<int, int>> a2;

    vector<vector<int>> adj1(n + 1), adj2(n + 1);
    for (int i = 1; i <= m1; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        adj1[a].push_back(b);
        adj1[b].push_back(a);
        a1.push_back({a, b});
    }

    int m2;
    cin >> m2;
    for (int i = 1; i <= m2; ++i) {
        int a, b;
        cin >> a >> b;
        if (a > b) swap(a, b);
        adj2[a].push_back(b);
        adj2[b].push_back(a);
        a2.insert({a, b});
    }

    vector<vector<int>> dp(n + 1, vector<int> (n + 1, inf));
    dp[s1][s2] = 0;
    set<pair<int, pair<int, int>>> pq;
    pq.insert({0, {s1, s2}});

    while (pq.size()) {
        auto node = *pq.begin();
        pq.erase(pq.begin());
        int dist = node.first, u = node.second.first, v = node.second.second;
        for (auto edge1 : adj1[u]) {
            for (auto edge2 : adj2[v]) {
                if (dp[edge1][edge2] > dist + abs(edge1 - edge2)) {
                    dp[edge1][edge2] = dist + abs(edge1 - edge2);
                    pq.insert({dp[edge1][edge2], {edge1, edge2}});
                }
            }
        }
    }


    int ans = inf;
    for (auto x : a1) {
        if (a2.find(x) != a2.end()) {
            ans = min((int)ans, dp[x.first][x.first]);
        }
    }

    cout << ((ans == inf) ? -1 : ans) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        solve();
    }

    return 0;
}
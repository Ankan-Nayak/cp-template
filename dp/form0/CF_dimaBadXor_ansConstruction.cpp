#include<bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n+1, vector<int>(m+1));
    vector<vector<int>> dp(n+2, vector<int>(1025));
    vector<vector<int>> parent(n+2, vector<int>(1025));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int x;  cin >> x;
            a[i][j] = x;
        }
    }

    dp[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int oldXor = 0; oldXor <= 1024; ++oldXor) {
            if (!dp[i - 1][oldXor]) continue;

            for (int j = 1; j <= m; ++j) {
                int newXor = oldXor ^ a[i][j];

                if (!dp[i][newXor]) {
                    dp[i][newXor] = 1;
                    parent[i][newXor] = j;
                }
            }
        }
    }


    int finalXor = -1;

    for (int xr = 1; xr <= 1024; ++xr) {
        if (dp[n][xr]) {
            finalXor = xr;
            break;
        }
    }

    if (finalXor == -1) {
        cout << "NIE\n";
        return 0;
    }

    cout << "TAK\n";

    vector<int> path;

    int xr = finalXor;
    for (int i = n; i >= 1; --i) {
        int col = parent[i][xr];
        path.push_back(col);

        xr ^= a[i][col];
    }
   
    reverse(path.begin(), path.end());
    for (auto it : path) cout << it << ' ';
   
    return 0;
}















#include<bits/stdc++.h>
using namespace std;


int n, m;
vector<vector<int>> a;
int dp[501][1024];
vector<int> path;

int f(int i, int curXor) {
    if (i > n) {
        return (curXor != 0);
    } 
    if (dp[i][curXor] != -1) return dp[i][curXor];
    int ans = 0;
    for (int j = 1; j <= m; ++j) {
        ans = f(i + 1, curXor^a[i][j]);
        if (ans) {
            path.push_back(j);
            break;
        }
    }
    
    return dp[i][curXor] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    
    cin >> n >> m;
    a.assign(n+1, vector<int>(m+1, 0));
    memset(dp, -1, sizeof(dp));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int x;  cin >> x;
            a[i][j] = x;
        }
    }

    bool flag = f(1, 0);
    if(!flag) {
        cout << "NIE\n";
        return 0;
    }

    cout << "TAK\n";
    reverse(path.begin(), path.end());
    for (auto it : path) cout << it << ' ';
   
    return 0;
}

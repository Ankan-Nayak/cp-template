#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

const int n = 8;
vector<int> q(n, -1);
char dp[n][n];

int check(int r, int c) {
    for (int row = 0; row < n; ++row) {
        if (abs(row - r) == abs(q[row] - c)  ||  c == q[row]) return 0;
    }
    return 1;
}

int rec(int level) {
    if (level == n) return 1;
    int ans = 0;
    for (int j = 0; j < n; ++j) {
        if (dp[level][j] == '.'  &&  check(level, j)) {
            q[level] = j;
            ans += rec(level + 1);
            q[level] = -1;
        }
    }
    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char ch;
            cin >> ch;
            dp[i][j] = ch;
        }
    }

    cout << rec(0);
    
    return 0;
}

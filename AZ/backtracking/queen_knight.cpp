#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

const int n = 15;
int N;
vector<int> q(n, -1);
char dp[n][n];

int check(int r, int c) {
    for (int row = 0; row < r; ++row) {
        int col = q[row];
        // queen attack
        if (abs(row - r) == abs(col - c)  ||  c == col) return 0;

        // knight attack
        if (abs(row - r) == 1  &&  abs(col - c) == 2) return 0;
        if (abs(row - r) == 2  &&  abs(col - c) == 1) return 0;
    }
    return 1;
}

int rec(int level) {
    if (level == N) return 1;
    int ans = 0;
    for (int j = 0; j < N; ++j) {
        if (check(level, j)) {
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

    cin >> N;

    cout << rec(0);
    
    return 0;
}

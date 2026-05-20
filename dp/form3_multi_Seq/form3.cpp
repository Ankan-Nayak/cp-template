/*
form 3
multi seq dp
multi array dp
dp(i, j, _) = best ans in (i in array a) and (j in array b)*/

/*
LCS in a, b
dp(i, j) = LCS of (i..N) and (j..M)*/


/*
dp(i,j) = best(dp(i+1, j), dp(i, j+1), 1 + dp(i+1,j+1))*/


#include<bits/stdc++.h>
using namespace std;

int dp[100][100];
int n, m;
string a, b;

int rec(int i, int j) {
    if (i >= n || j >= m) return 0;
    if (dp[i][j] != -1) return dp[i][j];
    int ans = 0;
    ans = max(ans, rec(i+1, j));
    ans = max(ans, rec(i, j+1));
    if (a[i] == b[j]) {
        ans = max(ans, rec(i+1, j+1) + 1);
    }
    return dp[i][j] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n >> m;
    cin >> a >> b;

    return 0;
}

#include<bits/stdc++.h>
using namespace std;

int dp[102][102][102];
string s1, s2, s3;
int n1, n2, n3;

int f(int i, int j, int k) {
    if (i >= n1  ||  j >= n2  ||  k >= n3) {
        return 0;
    }
    if (dp[i][j][k] != -1) return dp[i][j][k];
    int ans = 0;
    if (s1[i] == s2[j]  &&  s2[j] == s3[k]) {
        ans = max(ans, 1 + f(i + 1, j + 1, k + 1));
    }
    return dp[i][j][k] = max({ans, f(i + 1, j, k), f(i, j + 1, k), f(i, j, k + 1)});
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        cin >> s1 >> s2 >> s3;
        n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
        memset(dp, -1, sizeof(dp));
        cout << f(0, 0, 0) << endl;
    }
    return 0;
}

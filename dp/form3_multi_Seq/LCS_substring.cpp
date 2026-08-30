// LCS (subsequence):
// rec(n,m) is enough because you branch to all possibilities.

// LCSubstring:
// rec(i,j) describes a substring ENDING at (i,j),
// so you need to consider every possible ending (i,j).

int dp[1005][1005];

int rec(int i, int j) {
    if (i == 0 || j == 0)
        return 0;

    if (dp[i][j] != -1)
        return dp[i][j];

    if (a[i - 1] == b[j - 1]) {
        return dp[i][j] = 1 + rec(i - 1, j - 1);
    }

    return dp[i][j] = 0;
}

int longestCommonSubstring(string a, string b) {
    int ans = 0;

    memset(dp, -1, sizeof(dp));

    for (int i = 1; i <= a.size(); i++) {
        for (int j = 1; j <= b.size(); j++) {
            ans = max(ans, rec(i, j));
        }
    }

    return ans;
}
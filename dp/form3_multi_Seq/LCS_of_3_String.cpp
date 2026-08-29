


/*
        vector<vector<vector<int>>> dp(n1+1, vector<vector<int>> (n2+1, vector<int>(n3+1, 0)));

        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                for (int k = 1; k <= n3; ++k) {
                    if (s1[i - 1] == s2[j - 1]  &&  s2[j - 1] == s3[k - 1]) dp[i][j][k] = max(dp[i][j][k], 1 + dp[i - 1][j - 1][k - 1]);
                    dp[i][j][k] = max({dp[i][j][k], dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]});
                }
            }
        }

        cout << dp[n1][n2][n3] << '\n';
*/

int dp[210][210][210];

int rec(int i, int j, int k)
{
    if (i == n1 || j == n2 || k == n3)
        return 0;

    if (dp[i][j][k] != -1)
        return dp[i][j][k];

    int ans = 0;

    if (s1[i] == s2[j] && s2[j] == s3[k])
    {
        ans = 1 + rec(i + 1, j + 1, k + 1);
    }

    ans = max(ans, rec(i + 1, j, k));
    ans = max(ans, rec(i, j + 1, k));
    ans = max(ans, rec(i, j, k + 1));

    return dp[i][j][k] = ans;
}
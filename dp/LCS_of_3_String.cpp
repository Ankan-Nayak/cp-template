


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
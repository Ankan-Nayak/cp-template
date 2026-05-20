int f(int i, int j, int k) {
    if (i == a.size() || j == b.size() || k == c.size()) return 0;
    if (memo[i][j][k] != -1) return memo[i][j][k];
    
    int ans = max({f(i+1, j, k), f(i, j+1, k), f(i, j, k+1)});
    
    if (a[i] == b[j] && b[j] == c[k])
        ans = max(ans, f(i+1, j+1, k+1) + 1);
    
    return memo[i][j][k] = ans;
}




int lcs(string& a, string& b, string& c) {
    int n = a.size(), m = b.size(), p = c.size();
    
    for (int i = n; i >= 0; i--)
        for (int j = m; j >= 0; j--)
            for (int k = p; k >= 0; k--) {
                if (i == n || j == m || k == p) { dp[i][j][k] = 0; continue; }
                
                int ans = max({dp[i+1][j][k], dp[i][j+1][k], dp[i][j][k+1]});
                
                if (a[i] == b[j] && b[j] == c[k])
                    ans = max(ans, dp[i+1][j+1][k+1] + 1);
                
                dp[i][j][k] = ans;
            }
    return dp[0][0][0];
}
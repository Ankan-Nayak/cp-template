class Solution {
public:
    string s, t, ss;
    int n, m, K;
    int dp[110][110][205];
    int rec(int i, int j, int k) {
        if (i == n && j == m && k == K) return 1;
        if (dp[i][j][k] != -1) return dp[i][j][k];
        int ans = 0;
        if (i < n && k < K && s[i] == ss[k]) ans |= rec(i+1,j,k+1);
        if (j < m && k < K && t[j] == ss[k]) ans |= rec(i,j+1,k+1);
        return dp[i][j][k] = ans;
    }
    bool isInterleave(string s1, string s2, string s3) {
        n = s1.size(), m = s2.size(), K = s3.size();
        s = s1, t = s2, ss = s3;
        memset(dp, -1, sizeof(dp));
        bool ans = rec(0, 0, 0);
        return (ans==1);
    }
};


// but k is not needed as i + j = k
/*
so k can be removed from states
*/

class Solution {
public:
    string s, t, ss;
    int n, m, K;
    int dp[110][110];
    int rec(int i, int j) {
        if (i == n && j == m) return 1;
        if (dp[i][j] != -1) return dp[i][j];
        int ans = 0;
        int k = i + j;
        if (i < n && s[i] == ss[k]) ans |= rec(i+1,j);
        if (j < m && t[j] == ss[k]) ans |= rec(i,j+1);
        return dp[i][j] = ans;
    }
    bool isInterleave(string s1, string s2, string s3) {
        n = s1.size(), m = s2.size(), K = s3.size();
        s = s1, t = s2, ss = s3;
        if (n + m != K) return false;
        memset(dp, -1, sizeof(dp));
        bool ans = rec(0, 0);
        return (ans==1);
    }
};
class Solution {
public:
    int n;
    string s;
    int dp[1001][1001];

    bool pal(int i, int j) {
        if (i >= j)
            return true;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] != s[j])
            return dp[i][j] = false;

        return dp[i][j] = pal(i + 1, j - 1);
    }

    int countSubstrings(string str) {
        s = str;
        n = s.size();

        memset(dp, -1, sizeof(dp));

        int ans = 0;

        for (int l = 0; l < n; l++) {
            for (int r = l; r < n; r++) {
                ans += pal(l, r);
            }
        }

        return ans;
    }
};
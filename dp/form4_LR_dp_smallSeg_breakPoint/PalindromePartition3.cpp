class Solution {
public:
    int dp[101][101][101];
    int pal[101][101];
    const int inf = 1e9;
    string ss;
    int palrec(int l, int r) {
        if (l >= r) return 0;
        if (pal[l][r] != -1) return pal[l][r];
        int ans = 1e9;
        if (ss[l] == ss[r]) ans = min(ans, palrec(l+1, r-1));
        ans = min(ans, 1 + palrec(l+1, r-1));
        return pal[l][r] = ans;
    }
    int rec(int l, int r, int k) {
        if (r - l + 1 < k) return inf;
        if (k == 1) {
            return palrec(l,r);
        }
        if (dp[l][r][k] != -1) return dp[l][r][k];
        int ans = inf;
        for (int m = l; m < r; ++m) {
            ans = min(ans, rec(l, m, 1) + rec(m+1, r, k-1));
        }
        return dp[l][r][k] = ans;
    }
    int palindromePartition(string s, int k) {
        ss = s;
        memset(dp, -1, sizeof(dp));
        memset(pal, -1, sizeof(pal));
        return rec(0, s.size() - 1, k);
    }
};
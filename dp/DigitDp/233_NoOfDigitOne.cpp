class Solution {
public:
    string s;
    int dp[12][12][2];
    int rec(int i, int cnt, int tight) {
        if (i >= s.size()) {
            return cnt;
        }
        if (dp[i][cnt][tight] != -1) {
            return dp[i][cnt][tight];
        }
        int ans = 0;
        char ub = ((!tight) ? '9' : s[i]);
        for (char d = '0'; d <= ub; ++d) {
            int ct = ((d=='1')?cnt+1 : cnt);
            ans += rec(i+1, ct, (tight&(d==ub)));

        }
        return dp[i][cnt][tight] = ans;
    }
    int countDigitOne(int n) {
        memset(dp, -1, sizeof(dp));
        string ss = to_string(n);
        s = ss;
        int res = rec(0,0,1);
        return res;
    }
};
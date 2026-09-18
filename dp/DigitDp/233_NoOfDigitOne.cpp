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





class Solution {
public:
    string s;
    pair<int,int> dp[12][2];
    pair<int,int> rec(int i, int tight) {
        if (i >= s.size()) {
            return {0,1};
        }
        if (!(dp[i][tight].first == -1 && dp[i][tight].second == -1)) {
            return dp[i][tight];
        }
        int ones = 0, ways = 0;
        char ub = ((!tight) ? '9' : s[i]);
        for (char d = '0'; d <= ub; ++d) {
            auto [u,v] = rec(i+1, (tight&(d==ub)));
            ways += v;
            ones += u;
            if (d == '1') ones += v;

            /*
            1 needs to add whatever valid no comes
            1 + {1189} / {3211} / {2435}...
            the 1 contributes to all valid numbers so ones += ways
            ones is for all future 1s comes after which needs to return to return ans*/
        }
        return dp[i][tight] = {ones,ways};
    }
    int countDigitOne(int n) {
        for (int i = 0; i <= 11; ++i) {
            for (int j = 0; j < 2; ++j) {
                dp[i][j] = {-1,-1};
            }
        }
        string ss = to_string(n);
        s = ss;
        pair<int,int> res = rec(0,1);
        return res.first;
    }
};
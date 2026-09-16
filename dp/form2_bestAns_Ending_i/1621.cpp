class Solution {
public:
    int mod = 1e9+7;
    int N, K;
    int dp[1010][1010][2];
    int rec(int i, int k, int state) {
        if (k == K) return 1;
        if (i == N) {
            return 0;
        }
        if (dp[i][k][state] != -1) {
            return dp[i][k][state];
        }

        int ans = 0;

        if (state == 0) {
            ans = (ans + rec(i+1, k, 1) % mod) % mod;
            ans = (ans + rec(i+1, k, 0) % mod) % mod;
        }
        if (state == 1) {
            ans = (ans + rec(i, k+1, 0) % mod) % mod;
            ans = (ans + rec(i+1, k, 1) % mod) % mod;
        }
        return dp[i][k][state] = ans % mod;
    }
    int numberOfSets(int n, int k) {
        N = n, K = k;
        memset(dp, -1, sizeof(dp));
        // state = 0 -> last segment is not running
        return rec(0,0,0);
    }
};
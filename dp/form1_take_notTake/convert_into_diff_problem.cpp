class Solution {
public:
    int N;
    const int mod = 1e9 + 7;
    int dp[20005][6];

    int rec(int i, int prev) {
        if (i >= N - 1)
            return 1;

        if (dp[i][prev] != -1)
            return dp[i][prev];

        long long ans = 0;

        if (prev == 0) {
            ans += rec(i + 1, 1);
        }

        if (prev == 1) {
            ans += rec(i + 1, 0);
            ans += rec(i + 1, 2);
        }

        if (prev == 2) {
            ans += rec(i + 1, 0);
            ans += rec(i + 1, 1);
            ans += rec(i + 1, 3);
            ans += rec(i + 1, 4);
        }

        if (prev == 3) {
            ans += rec(i + 1, 2);
            ans += rec(i + 1, 4);
        }

        if (prev == 4) {
            ans += rec(i + 1, 0);
        }

        return dp[i][prev] = ans % mod;
    }

    int countVowelPermutation(int n) {
        N = n;
        memset(dp, -1, sizeof(dp));

        long long ans = 0;

        for (int i = 0; i < 5; ++i) {
            ans += rec(0, i);
        }

        return ans % mod;
    }
};

/*
ae
e a/i
i a/e/o/u
o i/u
u a

a e i o u
0 1 2 3 4

len = n
state -> i, prev
*/

// leetcode 1220
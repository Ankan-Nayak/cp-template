class Solution {
public:
    int n, m;
    string s1, s2;
    int dp[1010][1010];
    int rec(int i, int j) {
        if (i == n && j == m) return 0;
        if (i >= n) return m-j;
        if (j >= m) return n-i;
        if (dp[i][j] != -1) return dp[i][j];
        int ans = 1e9;
        if (s1[i] == s2[j]) {
            ans = min(ans, 1 + rec(i+1, j+1));
        }
        ans = min(ans, 1 + rec(i+1, j));
        ans = min(ans, 1 + rec(i, j+1));
        return dp[i][j] = ans;
    }

    string pathWay = "";
    void path(int i, int j) {
        if (i == n && j == m) return;
        if (i == n) {
            pathWay += s2[j];
            path(i, j+1);
            return;
        }
        if (j == m) {
            pathWay += s1[i];
            path(i+1, j);
            return;
        }
        int res1 = 1e9;
        if (s1[i] == s2[j]) res1 = rec(i+1, j+1) + 1;
        int res2 = 1 + rec(i+1, j);
        int res3 = 1 + rec(i, j+1);

        if (res1 <= res2 && res1 <= res3) {
            pathWay += s1[i];
            path(i+1, j+1);
        } else if (res2 <= res3) {
            pathWay += s1[i];
            path(i+1, j);
        } else {
            pathWay += s2[j];
            path(i, j+1);
        }
    }
    string shortestCommonSupersequence(string str1, string str2) {
        s1 = str1, s2 = str2;
        n = s1.size(), m = str2.size();
        memset(dp, -1, sizeof(dp));

        int ans = rec(0, 0);
        cout << ans << endl;
        path(0, 0);

        return pathWay;
    }
};


/*

or find LCS
+ add extra from str1
+ add extra from str2
*/
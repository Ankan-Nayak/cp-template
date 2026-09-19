class Solution {
public:
    int n, m;
    string ss, pp;
    int dp[25][25];
    int rec(int i, int j) {
        if (i == n && j == m) 
            return 1;

        if (j == m) 
            return 0;

        if (i == n) {
            // Current character followed by '*'
            if (j + 1 < m && pp[j + 1] == '*')
                return rec(i, j + 2);

            // Current character is '*'
            if (pp[j] == '*')
                return rec(i, j + 1);

            return 0;
        }
       


        if (i >= n) return 0;
        int ans = 0;
        if (dp[i][j] != -1) 
            return dp[i][j];

        if (pp[j] == '.') {
            ans |= rec(i+1, j+1);
        }

        if (ss[i] == pp[j]) {
            ans |= rec(i+1, j+1);
        }

        if (pp[j] == '*') {
            ans |= rec(i,j+1);

            if (j > 0 && (ss[i] == pp[j-1] || pp[j-1] == '.')) 
                ans |= rec(i+1,j);
        }

        if (j + 1 < m && pp[j + 1] == '*') {
            ans |= rec(i, j+2);
        }

        return dp[i][j] = ans;
    }
    bool isMatch(string s, string p) {
        n = s.size();
        m = p.size();
        ss = s, pp = p;
        memset(dp, -1, sizeof(dp));
        int ans = rec(0,0);
        return ans;
    }
};


/*

take examples
. has to be exsactly 1 char
x* = "", x, xx, xxx, xx...x
*/
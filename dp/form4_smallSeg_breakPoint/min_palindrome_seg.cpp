/*
()() no relation -> form2 -> 
()() merger -> form4 -> size of main array is changing
if we have to use bracket - - - (- - )(- -), probably LR dp
generally o(n^3) sol form4*/


class Solution {
public:
    int dp[2003][2003];
    int dp2[2003];
    string s;

    int rec1(int l, int r, string &s) {
        if (l >= r) return 1;
        if (dp[l][r] != -1) return dp[l][r];
        if (s[l] == s[r] && rec1(l + 1, r - 1, s)) 
            return dp[l][r] = 1;
        return dp[l][r] = 0;
    }

    int rec2(int i) {
        if (i == 0) return -1;
        if (dp2[i] != -1) return dp2[i];
        int ans = 1e9;
        for (int j = 0; j < i; j++) {
            if (rec1(j, i - 1, s)) {
                ans = min(ans, 1 + rec2(j));
            }
        }
        return dp2[i] = ans;
    }

    int minCut(string s) {
        this->s = s;
        int n = s.size();
        memset(dp, -1, sizeof(dp));
        memset(dp2, -1, sizeof(dp2));
        return rec2(n) ;
    }
};













#include<bits/stdc++.h>
using namespace std;

#define int long long
const int inf=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    string s;
    cin >> s;
    int n = s.size();

    vector<vector<int>> pali(n+1, vector<int>(n+1, inf));
    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i + len - 1 < n; ++i) {
            int j = i + len - 1;
            if (i == j) pali[i][j] = 1;
            else if (len == 2 && s[i] == s[j]) pali[i][j] = 1;
            else {
                if (s[i] == s[j]  &&  pali[i + 1][j - 1] == 1) pali[i][j] = 1;
            } 
        }
    }

    // Partition DP
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (pali[j][i] == 1) continue;

            for (int k = j; k < i; ++k) {
                pali[j][i] = min(pali[j][i],
                                 pali[j][k] + pali[k+1][i]);
            }
        }
    }

    cout << pali[0][n-1] - 1;

    
    return 0;
}

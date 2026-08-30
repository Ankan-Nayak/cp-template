/*
problem statement -> min insertion needed to make the string s palindrome
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
string s;
int dp[100][100];
const int inf = 1e9;

// if s[l]=s[r] -> rec(l+1,r-1)
// if (s[l] != s[r]) -> 1 + min(rec(l,r-1), rec(l+1,r))
// store min from all and return dp[l][r] = min(ans)
// if (l >= r) return 0;

int rec(int l, int r) {
    if (l >= r) {
        return 0;
    }
    if (dp[l][r] != -1) {
        return dp[l][r];
    }
    int ans = inf;
    if (s[l] == s[r]) {
        ans = min(ans, rec(l+1, r-1));
    } 
    ans = min(ans, 1 + min(rec(l+1,r), rec(l,r-1)));
    return dp[l][r] = ans;
}


signed main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;

    memset(dp, -1, sizeof(dp));

    cout << rec(0, s.size()-1) << '\n';

    return 0;
}
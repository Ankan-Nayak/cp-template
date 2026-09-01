#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int inf = 1e9+7;
 
 
int dp[20][10][2][2];
 
int solve(string &num, int n, int prev_digit, bool leading_zero, bool tight) {
    if (n == 0) return 1;
 
    if (dp[n][prev_digit][leading_zero][tight] != -1) return dp[n][prev_digit][leading_zero][tight];
 
    int ans = 0;
    int ub = tight ? (num[num.length() - n] - '0') : 9;
 
    for (int digit = 0; digit <= ub; ++digit) {
        if (prev_digit != digit  ||  (prev_digit == digit  &&  prev_digit == 0  &&  leading_zero)) ans += solve(num, n - 1, digit,  leading_zero & (digit==0), tight & (digit == ub));
    }
 
    return dp[n][prev_digit][leading_zero][tight] = ans;
}
 
int countNumbersWithSum(string &num) {
    memset(dp, -1, sizeof(dp));
    return solve(num, num.size(), -1, 1, 1);
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
 
    string L, R;
    cin >> L >> R;
 
 
 
    int ans_R = countNumbersWithSum(R);
 
 
    int ans_L = 0;
    if (L != "0") {
        // Decrement L to calculate the range [L, R]
        int i = L.size() - 1;
        while (i >= 0 && L[i] == '0') {
            L[i] = '9';
            --i;
        }
        if (i >= 0) L[i]--; 
 
        ans_L = countNumbersWithSum(L);
    }
 
    cout << ans_R - ans_L << endl;
 
    return 0;

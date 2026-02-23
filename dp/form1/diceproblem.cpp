//  _ _ i_ _ _ _
// move i + 1, i + 2...


#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int mod = 1e9+7;
 
vector<int> dp;
int n;
 
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
 
 
    cin >> n;
    dp.resize(n + 10, 0);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int d = 1; d <= 6; ++d) {
            if (i - d >= 0) {
                dp[i] = (dp[i] + dp[i - d]) % mod;
            }
        }
    }
    cout << dp[n];
 
    return 0;
}
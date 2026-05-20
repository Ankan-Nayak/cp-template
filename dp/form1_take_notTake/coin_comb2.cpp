/*
all unq
use i type of coin at its time any time.. then never use it again*/

#include<bits/stdc++.h>
using namespace std;
 
#define int long long
const int mod = 1e9+7;
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
 
    
    int n, target;
    cin >> n >> target;
    vector<int> coin(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> coin[i];
    }
    sort(coin.begin() + 1, coin.end());
 
    vector<int> dp(target + 10, 0);
    dp[0] = 1; 
 
    for (int j = 1; j <= n; ++j) {
        for (int i = 0; i <= target; ++i) {
            if (i - coin[j] >= 0) {
                (dp[i] += dp[i - coin[j]]) %= mod;
            }
        }
    }
    cout << dp[target];
    return 0;
}
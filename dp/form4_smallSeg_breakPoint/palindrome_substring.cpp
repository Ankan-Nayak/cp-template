// 11
// 1 3 2 3 2 4 3 3 4 3 1
// (2 3 2), (1 4 3 3 4 3 1) ans = 2

// 3 2 3 2 4 3 3 4 3 1
// (2 3 2), (3 4 3 3 4 3), (1) ans = 3

#include <bits/stdc++.h>
using namespace std;

int dp[105][105], a[105];
int n;

int main(){
    int T; cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 0; i < n; i++) cin >> a[i];
        
        memset(dp, 0, sizeof(dp));
        
        for(int i = 0; i < n; i++) dp[i][i] = 1;
        
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i <= n-len; i++) {
                int j = i + len - 1;
                dp[i][j] = len; // worst case
                
                // Split
                for(int k = i; k < j; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                
                // If ends match, we can do better
                if(a[i] == a[j]) {
                    if(len == 2) dp[i][j] = 1;
                    else dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
                }
            }
        }
        cout << dp[0][n-1] << "\n";
    }
}




#include <bits/stdc++.h>
using namespace std;

int dp[105][105], a[105];
int n;

int main(){
    int T; cin >> T;
    while(T--) {
        cin >> n;
        for(int i = 0; i < n; i++) cin >> a[i];
        
        memset(dp, 0, sizeof(dp));
        
        for(int i = 0; i < n; i++) dp[i][i] = 1;
        
        for(int len = 2; len <= n; len++) {
            for(int i = 0; i <= n-len; i++) {
                int j = i + len - 1;
                dp[i][j] = len; // worst case
                
                // Split
                for(int k = i; k < j; k++)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                
                // If ends match, we can do better
                if(a[i] == a[j]) {
                    if(len == 2) dp[i][j] = 1;
                    else dp[i][j] = min(dp[i][j], dp[i+1][j-1]);
                }
            }
        }
        cout << dp[0][n-1] << "\n";
    }
}
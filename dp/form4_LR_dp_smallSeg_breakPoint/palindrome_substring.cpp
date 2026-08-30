// 11
// 1 2 3 2 4 3 3 4 3 1
// (2 3 2), (1 4 3 3 4 3 1) ans = 2

// 3 2 3 2 4 3 3 4 3 1
// (2 3 2), (3 4 3 3 4 3), (1) ans = 3

// [a {_ _ _ _ } a] [b _ _ b]
// if {} this cost x, then [a {_ _ _ _ } a] also cost x, 
// when deleting the last seg palindrome inside {} make it a{}a that's it


/*
Palindrome Partitioning
Recursive DP version
--------------------------------

State:
dp(i) = minimum cuts needed
for substring s[i...n-1]

Transition:
Try every possible palindrome starting from i

Example:
"aab"

aa | b

Answer = 1
--------------------------------
*/

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:

    string s;
    int n;

    int dp[2005];
    int pal[2005][2005];



    // check palindrome
    int isPal(int l, int r) {

        if(l >= r)
            return 1;

        if(pal[l][r] != -1)
            return pal[l][r];

        if(s[l] == s[r] && isPal(l+1,r-1))
            return pal[l][r] = 1;

        return pal[l][r] = 0;
    }



    /*
    rec(i)

    minimum cuts needed
    for substring s[i...n-1]
    */
    int rec(int i) {

        // no characters left
        if(i == n)
            return -1;

        if(dp[i] != -1)
            return dp[i];

        int ans = 1e9;




        // make palindrome from i...j
        for(int j=i;j<n;j++) {

            if(isPal(i,j)) {

                ans = min(
                    ans,
                    1 + rec(j+1)
                );
            }
        }

        return dp[i] = ans;
    }



    int minCut(string str) {

        s = str;
        n = s.size();

        memset(dp,-1,sizeof(dp));
        memset(pal,-1,sizeof(pal));

        return rec(0);
    }
};


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
/*
_ _ _ _ _ _ _
  i
_ _ _ _ _ _ _
        j

seperate structure
*/


#include <bits/stdc++.h>
using namespace std;
 
const int inf = 1e7;
 
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);cout.tie(0);
 
  string s1, s2;
  cin >> s1 >> s2;
  int n = s1.size(), m = s2.size();
  vector<vector<int>> dp(n + 2, vector<int> (m + 2, inf));  
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {
      if (i == 0) {
        dp[i][j] = j;
      }
      else if (j == 0) {
        dp[i][j] = i;
      }
      else if (s1[i - 1] == s2[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      }
      else {
        dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
      }
    }
  }
  cout << dp[n][m];
  
  return 0;
}
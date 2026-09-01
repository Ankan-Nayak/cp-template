#include <bits/stdc++.h>
using namespace std;
 
#define int long long
 
int n, total = 0;
vector<int> a;
vector<vector<int>> dp(5002, vector<int>(5002, -1));
 
int solve(int i, int j) {
  if (i == j) return a[i]; 
  if (i + 1 == j) return max(a[i], a[j]);
  if (i > j) return 0;
  if (dp[i][j] != -1) return dp[i][j];
 
  return dp[i][j] = max(a[i] + min(solve(i + 1, j - 1), solve(i + 2, j)), a[j] + min(solve(i + 1, j - 1), solve(i, j - 2)));
}
 
signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
 
  cin >> n;
  a.resize(n + 1);
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int res = solve(1, n);
  cout << res;
  return 0;
}

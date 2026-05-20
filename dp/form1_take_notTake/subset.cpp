/* thinking process
1. always think Recursive DP and relation -> f(i, j) = min(1 + f(i - k, j) + f(k, j), 1 + f(i, j - k) + f(i, k))
2. think base cases also from RECURSIVE DP -> when i == j return 0 => dp[i][j] = 0 (if i == j)
3. think order of loop from RECURSIVE DP
 
4. convert all this logic now in ITERATIVE DP, carefull for boundary
5. take best case as BASE CASE, rest un-reachable cases should remain un reachable(inf or -inf)
6. Don't update random cases as base because during updation ans might change
*/


int f(int pos, int sum) {
    if (sum == 0) return 1;
    if (pos == n) return 0;
    if (dp[pos][sum] != -1) return dp[pos][sum];
    int ans = 0;
    ans = max(ans, f(pos + 1, sum));
    if (c[pos] <= sum) ans = max(ans, f(pos + 1, sum - c[pos]));
    return dp[pos][sum] = ans;
}

 
 
#include<bits/stdc++.h>
using namespace std;
 
const int inf=1e9;
 
signed main() {
 
    int n;
    cin >> n;
    vector<int> c(n);
    for (int j = 0; j < n; ++j) cin >> c[j];
    sort(c.begin(), c.end());
 
    vector<int> dp(1e5 + 10, 0);
    dp[0] = 1;
 
    for (int j = 0; j < n; ++j) {
        for (int i = 1e5; i >= 1; --i) {
            if (c[j] <= i) dp[i] = max(dp[i], dp[i - c[j]]);
        }
    }
 
    set<int> st;
    for (int i = 1; i <= 1e5; ++i) if (dp[i]) st.insert(i);
 
    cout << st.size() << '\n';
    for (auto it : st) cout << it << ' ';
    return 0;
}

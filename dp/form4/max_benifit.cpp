#include<bits/stdc++.h>
using namespace std;

#define int long long
const int inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // Prefix sum for O(1) range sum
    vector<int> pref(n+1, 0);
    for (int i = 0; i < n; i++)
        pref[i+1] = pref[i] + a[i];

    auto getSum = [&](int l, int r) {
        return pref[r+1] - pref[l];
    };

    // dp[i][j] = max benefit for range [i..j]
    vector<vector<int>> dp(n, vector<int>(n, -inf));

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            if (i == j) {
                dp[i][j] = 0;
                continue;
            }

            for (int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j],
                               dp[i][k] + dp[k+1][j]
                               + (getSum(i, k)%100) * (getSum(k+1, j) %100)); // (getSum(i, k)%100) * (getSum(k+1, j) %100) % 100 this is wrong because extra % 100 changes contribution value, be aware
            }
        }
    }

    cout << dp[0][n-1];
    return 0;
}

/*
Example:
a = [4, 1, 5]

Merge rule:
gain = (sum of left segment) × (sum of right segment)

Option 1:
[4, 1, 5]
→ merge (4,1) → gain = 4×1 = 4 → [5, 5]
→ merge (5,5) → gain = 5×5 = 25
Total = 4 + 25 = 29

Option 2:
[4, 1, 5]
→ merge (1,5) → gain = 1×5 = 5 → [4, 6]
→ merge (4,6) → gain = 4×6 = 24
Total = 5 + 24 = 29

Goal:
Maximize total gain after fully merging array

DP Meaning:
dp[i][j] = maximum gain from subarray [i..j]
sum[i][j] = sum of elements from [i..j]

Transition:
dp[i][j] = max over k in [i..j-1]:
           dp[i][k] + dp[k+1][j] + sum[i][k] × sum[k+1][j]
*/





/*


[L    mid] [mid+1   R]
 _ _ _ _ _ _ _ _
     _   _
       _
      
   
known(max sum from left(x) * max sum from right(y)) + unknown(max benifit from left * max benifit from right)

dp(l,r) = max(dp(l,mid) + dp(mid+1,r) + x*y)

0(n^2)[state] * 0(n)[for transition] => 0(n^3)
*/


#include<bits/stdc++.h>
using namespace std;

int n;
int a[500];
int dp[500][500];

int rec(int l, int r) {
    if (l == r) return 0;
    if (dp[l][r] != -1) return dp[l][r];

    int total = 0;
    int ans = 0;
    int sum =0 ;
    for (int i = l; i <= r; ++i) total += a[i];

    
    for (int mid = l; mid < r; ++mid) {
        sum += a[mid];
        ans = max(ans, + rec(l, mid) + rec(mid+1, r) + (sum%100)*(total-sum)%100);
    }
    return dp[l][r] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    memset(dp, -1, sizeof(dp));
    cout << rec(0, n-1);

    return 0;
}

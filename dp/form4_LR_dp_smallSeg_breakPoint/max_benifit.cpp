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





// int rec(int l, int r) {
//     if (l>=r) return 0;
//     if (dp[l][r] != -1) return dp[l][r];
//     int ans = 1e18;
//     for (int m = l; m < r; ++m) {
//         ans = min(ans, rec(l, m) + rec(m+1, r) + (getSum(l,m)%100) * (getSum(m+1,r)%100));
//     }
//     return dp[l][r] = ans;
// }



#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
ll a[505];
ll pref[505];
ll dp[505][505];

ll getSum(int l, int r) {
    return pref[r] - pref[l - 1];
}

ll normMod(ll x) {
    // safe mod that always returns a value in [0, 99], even for negative x
    return ((x % 100) + 100) % 100;
}

ll rec(int l, int r) {
    if (l >= r) return 0;
    if (dp[l][r] != -1) return dp[l][r];

    ll ans = LLONG_MAX;
    for (int m = l; m < r; ++m) {
        ll left = rec(l, m);
        ll right = rec(m + 1, r);
        ll cost = normMod(getSum(l, m)) * normMod(getSum(m + 1, r));
        ans = min(ans, left + right + cost);
    }

    return dp[l][r] = ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }

    memset(dp, -1, sizeof(dp));

    cout << rec(1, n) << "\n";

    return 0;
}


/*

merge element 2

by mergeing 2 element(a,b) you get a single element (ax + by + z) % 50
cost = a * b

rec(l,r,x)


*/


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;      // ⚠️ inferred — actual bound not visible; adjust to problem's N constraint
int n;
int a[MAXN];
int X, Y, Z;                // merge formula constants — read from input
int memo[MAXN][MAXN][50];
bool done_[MAXN][MAXN];      // renamed from `done` to avoid clashing with std::done if any

int dp(int l, int r, int xx) {
    if (l == r) {
        if (a[l] == xx) return 0;
        else return 1e9;
    }

    if (done_[l][r]) {
        return memo[l][r][xx];
    }

    for (int i = 0; i < 50; i++) memo[l][r][i] = 1e9;

    for (int mid = l; mid < r; mid++) {
        for (int fs = 0; fs < 50; fs++) {
            for (int ls = 0; ls < 50; ls++) {
                int merged = (fs * X + ls * Y + Z) % 50;
                memo[l][r][merged] = min(
                    memo[l][r][merged],
                    dp(l, mid, fs) + dp(mid + 1, r, ls) + fs * ls
                );
            }
        }
    }

    done_[l][r] = 1;
    return memo[l][r][xx];
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> X >> Y >> Z;

    int target;              // ⚠️ inferred — assumes the task asks for a specific final value
    cin >> target;

    memset(done_, 0, sizeof(done_));
    int ans = dp(0, n - 1, target);

    if (ans >= (int)1e9) cout << -1 << "\n";
    else cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    // cin >> t;             // ⚠️ uncomment if multiple test cases
    while (t--) solve();

    return 0;
}


// dp(l, r, xx) = minimum cost to merge the subarray [l, r] down into a single value equal to xx.
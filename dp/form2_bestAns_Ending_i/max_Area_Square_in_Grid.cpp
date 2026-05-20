#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n+1, vector<int> (m+1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
            }
        }

        vector<vector<int>> dp(n+1, vector<int> (m+1));
        // dp[i][j] = side length of the largest square 
        //    whose bottom-right corner is (i, j)

        int len = 0;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (a[i][j] == 1) {
                    dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]});
                }

                len = max(len, dp[i][j]);
            }
        }
        cout << len << '\n';
    }
    return 0;
}
















// another solution

#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
            }
        }

        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                dp[i][j] = a[i][j] + dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1];
            }
        }

        auto check = [&](int mid) ->bool {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    int l = i - mid + 1, r = j - mid + 1;
                    if (l < 1  ||  r < 1) continue;

                    int sum = dp[i][j] - dp[l - 1][j] - dp[i][r - 1] + dp[l - 1][r - 1];
                    if (sum == mid * mid) return true;
                }
            }
            return false;
        };

        int low = 1, high = min(n, m), ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        cout << ans * ans << endl;
    }
    return 0;
}
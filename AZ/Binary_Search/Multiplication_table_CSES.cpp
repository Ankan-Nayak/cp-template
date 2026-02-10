#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n;
    cin >> n;

    int k = (n*n + 1) / 2;

    // in matrix, not possible to generate all
    auto check = [&](int mid)->bool {
        // k th value
        // (no of  elems <= X) >= k,    [ct = no of  elems, X = mid here]
        // like k th sum problem
        int ct = 0;
        for (int i = 1; i <= n; ++i) {
            ct += min(n, mid / i);
        }
        return ct >= k;
    };

    int low = 0, high = n * n, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    cout << ans;
    return 0;
}

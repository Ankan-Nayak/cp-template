#include<bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n + 1), pref(n + 1);
        
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }
        
        auto check = [&](int mid) ->bool {
            for (int i = mid; i <= n; ++i) {
                int no_of_one = pref[i] - pref[i - mid];
                int no_of_zero = mid - no_of_one;
                if (no_of_zero <= k) return true;
            }
            return false;
        };

        int low = 0, high = n, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            // mid = no of conseq 1
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        
        cout << ans << '\n';
    }
    return 0;
}



// minimise (maximum neighbour distance)


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
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin>> a[i];
        }
        sort(a.begin(), a.end());
        auto check = [&](int mid)-> bool {
            int ct = 0;
            for (int i = 1; i < n; ++i) {
                ct += (a[i] - a[i - 1] + mid - 1) / mid - 1;
            }
            return (ct <= k);
        };

        // if low = 0, compile error, as x / 0, undefined
        int low = 1, high = a[n - 1], ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

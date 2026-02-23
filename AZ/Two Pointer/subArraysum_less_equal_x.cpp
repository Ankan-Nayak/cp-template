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
        int n;
        cin >> n;
        vector<int> a(n+1);
        int low = 0, high = 0, ans = 0;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            high += a[i];
        }

        auto check = [&](int mid)-> int {
            int i = 1, j = 1, curSum = 0, ct = 0;
            while (i <= n) {
                curSum += a[i];
                while (j <= i && curSum > mid) {
                    curSum -= a[j];
                    j += 1;
                }
                ct += (i - j + 1);
                i += 1;
            } 
            return ct;
        };

        int subArray = n * (n + 1) / 2;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int cnt = check(mid); // find no of subarrays whose sum is <= x
            if (cnt >= (subArray + 1) / 2) { 
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

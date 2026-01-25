// [1, 3, 4, 9, 11] -> roate 2 times
// [9, 11, 1, 3, 4] -> all unq, how many times rotated, in min transaction_safe

// BS 
// check function on [9, 11, 1, 3, 4]
// we have to find index of min value, how much shifted 
// arr[mid] < arr[0] or, min pos
// arr[mid] < arr[n - 1], min pos

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
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        auto check = [&](int mid)->bool {
            return a[mid] <= a[n -1];
        };
        int low = 0, high = n - 1, ans = -1, loop = 100;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
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






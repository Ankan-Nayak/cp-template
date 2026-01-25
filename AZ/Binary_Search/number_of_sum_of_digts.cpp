// given N, S
// count positive numbers such that
// X <= N  && (X - sod(X) >= S) , X is a number

// use BS on 1 to X, 
// now do check BS if a number satisfies X-sod(X)>= S, all after that will satisfy


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
        int n, s;
        cin >> n >> s;
        auto check = [&](int mid)->bool {
            int num = mid, sod = 0;
            while (num > 0) {
                sod += num % 10;
                num /= 10;
            }
            int m = mid - sod;
            return m >= s;
        };
        int low = 1, high = n, ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        if (ans == -1) {
            cout << 0 << endl;
        } else {
            cout << n - ans + 1 << endl;
        }

    }
    return 0;
}




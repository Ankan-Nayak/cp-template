// Description
// You are given N balls and an integer K. The color of each ball is given in an array A. A basket is filled if it contains at least 
// K balls of different colors. Find the maximum number of filled baskets you can get if you optimally put the balls in the baskets.



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
        map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            int x;
            cin >> x;
            mp[x] += 1;
        }
        auto check = [&](int mid)->bool {
            int s = 0;
            for (auto it : mp) {
                if (it.second > mid) s += mid;
                else s += it.second;
            }
            return s / k >= mid;
        };
        int low = 0, high = n / k, ans = -1, loop = 100;
        while (low <= high) {
        int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}


// mid = 7, k = 3
// max I can take is len(", .)
// * * * * . . .
// . . . . _ _ "
// " " " " " " ;

// overalp, look .
// total_sum / mid >= k
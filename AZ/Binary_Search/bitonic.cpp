 
//    .
//   . .
//  .   .
// .     .

// if (a[mid] > a[mid + 1])
// BS works for int values great
// for floating use Ternary Search -> removes 1 / 3 every time, inferiror technique

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
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        auto check = [&](int mid)->bool {
            if (mid == n - 1) return true;
            return a[mid] > a[mid + 1];
        };
        int low = 0, high = n - 1, peak = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                peak = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }

        // cout << "peak " << peak << endl;


        while (q--) {
            int x;
            cin >> x;
            vector<int> pos;
        
            int low = 0, high = peak - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (a[mid] == x) {
                    pos.push_back(mid); 
                    break;
                }
                else if (a[mid] > x) high = mid - 1;
                else low = mid + 1;
            }

            low = peak + 1, high = n - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (a[mid] == x) {
                    pos.push_back(mid); 
                    break;
                }
                else if (a[mid] > x) low = mid + 1;
                else high = mid - 1;
            }

            if (a[peak] == x) pos.push_back(peak);

            for (auto it : pos) cout << it + 1 << ' ';
            cout << endl;
        }
        
    }
    return 0;
}




// bitonic array
// mountain
// 1 3 10 20 14 3  (ans = 20)  or   1 2 3 4 5
// check function -> arr[mid] > arr[mid + 1] -> 1 3 10 20 14 3 -inf, min pos



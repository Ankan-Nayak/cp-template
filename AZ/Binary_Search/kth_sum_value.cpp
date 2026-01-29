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
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(n), b(m);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < m; ++i) {
            cin >> b[i];
        }

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        auto check = [&](int mid) ->bool{
            int index = 0, j = m - 1;
            for (int i = 0; i < n; ++i) {
                while (j >= 0  &&  a[i] + b[j] > mid) {
                    j -= 1;
                }
                if (a[i] + b[j] <= mid) index += (j + 1);
            }
            return (index >= k);
        };

        int low = a[0] + b[0], high = a[n - 1] + b[m -1], ans = -1;
        while (low <= high) {
            // mid = kth sum to verify
            int mid = low + (high - low) / 2;
            // mid = 7;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
            // break;
        }
        cout << ans << '\n';
    }
    return 0;
}

// optimal 0((n + m)logn)



#include<bits/stdc++.h>
using namespace std;

#define int long long

bool check(int mid, vector<int>& a, vector<int>& b, int n, int m, int k) {
    long long count = 0;
    for (int i = 0; i < n; ++i) {
        // Count how many b[j] satisfy a[i] + b[j] <= mid
        count += upper_bound(b.begin(), b.end(), mid - a[i]) - b.begin();
        if (count >= k) return true;
    }
    return count >= k;
}


// Must use 'signed main()' instead of 'int main()
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(n), b(m);
        
        for (int i = 0; i < n; ++i) cin >> a[i];
        for (int i = 0; i < m; ++i) cin >> b[i];

        sort(a.begin(), a.end());
        sort(b.begin(), b.end());

        if (n > m) {
            swap(n,m);
            swap(a,b);
        }
        int low = a[0] + b[0], high = a[n - 1] + b[m - 1], ans = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid, a, b, n, m, k)) {
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


// Summary
// The swap optimization ensures you always iterate over the smaller array and binary search on the larger array. This minimizes the total number of operations, which is critical when one array is much larger than the other.













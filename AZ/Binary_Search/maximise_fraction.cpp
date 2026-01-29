// Given two arrays A and B of size N and an integer K.
// Select K indices such that:
//   sum(A[i1] + A[i2] + ... + A[iK]) / sum(B[i1] + B[i2] + ... + B[iK])
// is maximized.

// Output the maximum ratio rounded to 6 decimal places.

// Constraints:
// - 1 ≤ T ≤ 10000
// - 1 ≤ N ≤ 10^4
// - 1 ≤ K ≤ N
// - 1 ≤ A[i], B[i] ≤ 10^4
// - Sum of N across all test cases ≤ 10^5

// Input:
// T (test cases)
// For each test case:
//   N K
//   A[1] A[2] ... A[N]
//   B[1] B[2] ... B[N]

// Output:
// For each test case, print the maximum ratio with 6 decimal places.



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
        vector<long double> a(n), b(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }
        auto check = [&](long double mid) -> bool {
            priority_queue<long double> pq; // max heap
            for (int i = 0; i < n; ++i) {
                pq.push(a[i] - mid * b[i]);
            }
            long double sum = 0.0;
            for (int i = 0; i < k; ++i) {
                sum += pq.top();
                pq.pop();
            }
            return sum >= 0;
        };
        
        long double low = 0, high = 1e8, ans = 0, loop = 200; // (loop--)
        long double eps = 1e-9; // 1e6 thakle, 1e9, sue 3 extra
        // for (int i = 0; i < n; ++i) high = max(high, a[i]*1.00 / b[i]); don't do it in decimal q while () h *= 2;
        while (abs(low - high) > eps) {
            long double mid = (low + high) / 2;
            if (check(mid)) {
                ans = mid;
                low = mid; // not mid + 1 in decimals
            } else {
                high = mid;
            }
        }
        
        cout << fixed << setprecision(6) << ans << endl;
    }
    return 0;
}























// Not gonna work


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
        vector<long double> a(n), b(n), num(n), denom(n), ans(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        for (int i =0; i < n; ++i) {
            cin >> b[i];
        }

        vector<pair<long double, int>> p;
        for (int i = 0; i < n; ++i) {
            p.push_back({a[i] / b[i], i});
        }

        sort(p.rbegin(), p.rend());

        // for (int i = 0; i <= n; ++i) {
        //     cout << p[i].second << ' ' << p[i].first << endl;
        // }

        for (int i = 0; i < n; ++i) {
            num[i] = a[p[i].second];
            denom[i] = b[p[i].second];
            if (i > 0) {
                num[i] += num[i - 1];
                denom[i] += denom[i - 1];
            }

            ans[i] = num[i] / denom[i];

            // cout << p[i].second << ' ';
        }        
        
        cout << ans[k - 1] << endl;
    }
    return 0;
}



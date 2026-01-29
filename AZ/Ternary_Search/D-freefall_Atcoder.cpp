//cp algorithm code, once r - l < 3 stop, it's not possible to to chose mid1, mid2
/*double ternary_search(double l, double r) {
    double eps = 1e-9;              //set the error limit here
    while (r - l > eps) {   // r - l >= 3 will work or r - l > 3
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      //evaluates the function at m1
        double f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                   //return the maximum of f(x) in [l, r]
}*/
//if x is increasing at top and started decreasing for [low to high] range, ternary search helps to find x
//    .
//   .  .
// .      .
//.         .
/*------------------------------------------------------------------------------------------------------------------------------------------*/





#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

ll a, b;

ld func(ll op) {
    return (ld)b * op + (ld)a / sqrt((ld)op + 1.0L);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    ll lo = 0, hi = (a + b - 1) / b;

    // integer ternary search
    while (hi - lo > 3) {
        ll mid1 = lo + (hi - lo) / 3;
        ll mid2 = hi - (hi - lo) / 3;

        if (func(mid1) > func(mid2))
            lo = mid1;
        else
            hi = mid2;
    }

    // brute force on small range
    ld ans = func(lo);
    for (ll i = lo + 1; i <= hi; i++) {
        ans = min(ans, func(i));
    }

    cout << fixed << setprecision(15) << ans << "\n";
    return 0;
}







#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;

ll a, b;

ld func(ll op) {
    return (ld)b * op + (ld)a / sqrt((ld)op + 1.0L);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    ll lo = 0, hi = (a + b - 1) / b, ans = 0;

    // integer ternary search -> covert -> Bs
    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;

        if (func(mid) <= func(mid + 1)) {
            ans = mid;
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
    }

    cout << fixed << setprecision(15) << func(ans) << "\n";
    return 0;
}

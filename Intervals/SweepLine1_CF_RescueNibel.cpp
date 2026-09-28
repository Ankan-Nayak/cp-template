#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 998244353;

int binpow(int a, int b) {
    if(b == 0) return 1;
    if(b % 2 == 1) return (a * binpow(a, b-1)) % mod;
    else {
        int x = binpow(a, b/2);
        return (x * x) % mod;
    }
}

int inverse(int x) {    // O(log(mod))
    return binpow(x, mod-2);
}

int fact[1000100];
int invfact[1000100];

void precompute_for_faster() {    // O(n) + O(log(mod)) + O(n) ~ O(n + log(mod))
    fact[0] = 1;
    for(int i = 1; i <= 1000000; i++) { // fixed from i=1
        fact[i] = (fact[i-1] * i) % mod;
    }
    invfact[1000000] = inverse(fact[1000000]);
    for(int i = 1000000; i >= 1; i--) {
        invfact[i-1] = (invfact[i] * i) % mod;
    }
}

int ncr_fact_faster(int n, int r) {    // O(1)
    if(r < 0 || r > n) return 0;       // added guard
    int num = fact[n];
    int den = (invfact[n-r] * invfact[r]) % mod;
    return (num * den) % mod;    // den is already inverted
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<int> l, r;
    for (int i = 0; i < n; ++i) {
        int L, R;
        cin >> L >> R;

        l.push_back(L);
        r.push_back(R);
    }

    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    precompute_for_faster();

    int i = 0, j = 0, lamp = 0, ans = 0;
    while (i < n && j < n) {
        if (l[i] <= r[j]) {
            if (lamp >= k-1) {
                ans += ncr_fact_faster(lamp, k-1) % mod;
                ans %= mod;
            }
            lamp += 1;
            i += 1;
        } else {
            lamp -= 1;
            j += 1;
        }
    }
    cout << ans << endl;

    return 0;
}
/*
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
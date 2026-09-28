events.push_back({l, +1});
events.push_back({r + 1, -1});
sort __ENVIRONMENT_MAC_OS_X_VERSION_MIN_REQUIRED__for (int i = 0; i < events.size(); ) {

    int x = events[i].first;
    int change = 0;

    while (i < events.size() && events[i].first == x) {
        change += events[i].second;
        i++;
    }

    active += change;

    // active applies from x until the next event
}


coordinate   change
-------------------
2             +1
4             +1
4             +1
6             -1
7             -1
8             -1




The problem asks you to:
Choose any k intervals, find their common intersection, count how many integer
points are inside that intersection, 
and add this count for every possible group of k intervals.

coordinate     change      curr       active intervals
-------------------------------------------------------
1              +1           1          A
2              +1           2          A,B
4              +1           3          A,B,C
6              -1           2          B,C
7              -1           1          C
8              -1           0          nothing

for 2 consequtuve distances if any lamp is active then calculate
the contribution of that particular distance

i, i+1 -> how many lamps active? let's say x(x >= k)
contri -> (i+1 - i) * C(x, k)

1 → 2
2 → 4
4 → 6
6 → 7
7 → 8


#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 1e9+7;

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

    map<int, int> active;
    for (int i = 0; i < n; ++i) {
        int L, R;
        cin >> L >> R;

        active[L] += 1;
        active[R+1] -= 1;
    }
  

    precompute_for_faster();

    int lamp = 0, ans = 0;

    vector<int> endPoint;
    for (auto it : active) endPoint.push_back(it.first);

    for (int i = 0; i + 1 < endPoint.size(); ++i) {
        lamp += active[endPoint[i]];
        int part = endPoint[i+1] - endPoint[i];
        if (lamp >= k) {
            ans = (ans + ((ncr_fact_faster(lamp, k) % mod) * part) % mod) % mod;
        }
    }
    
    cout << ans << endl;

    return 0;
}
/*
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
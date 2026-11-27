// dp + sement tree + offset

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int sz;                 // number of distinct values
vector<long long> t;    // segment tree storing sums (mod MOD)

// Point update: dp[pos] += val
void update(int node, int lo, int hi, int pos, long long val) {
    if (lo == hi) {
        t[node] = (t[node] + val) % MOD;    // accumulate (same value can appear many times)
        return;
    }
    int mid = (lo + hi) / 2;
    if (pos <= mid) update(2 * node, lo, mid, pos, val);
    else            update(2 * node + 1, mid + 1, hi, pos, val);
    t[node] = (t[2 * node] + t[2 * node + 1]) % MOD;
}

// Range sum query over [l, r]
long long query(int node, int lo, int hi, int l, int r) {
    if (l > r || r < lo || hi < l) return 0;    // outside range: identity for sum
    if (l <= lo && hi <= r) return t[node];     // fully inside
    int mid = (lo + hi) / 2;
    return (query(2 * node, lo, mid, l, r) +
            query(2 * node + 1, mid + 1, hi, l, r)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &x : a) cin >> x;

    // ---------- coordinate compression ----------
    vector<int> sorted_vals = a;
    sort(sorted_vals.begin(), sorted_vals.end());
    sorted_vals.erase(unique(sorted_vals.begin(), sorted_vals.end()), sorted_vals.end());
    sz = sorted_vals.size();

    t.assign(4 * sz, 0);

    // ---------- process elements left to right ----------
    for (int i = 0; i < n; i++) {
        // compressed index r of a[i]
        int r = lower_bound(sorted_vals.begin(), sorted_vals.end(), a[i]) - sorted_vals.begin();

        // cnt = subsequences ending at a strictly smaller value, in [0, r-1]
        long long cnt = (r > 0) ? query(1, 0, sz - 1, 0, r - 1) : 0;

        // extend all of them by a[i], plus the single-element subsequence [a[i]]
        update(1, 0, sz - 1, r, (cnt + 1) % MOD);
    }

    // ---------- answer = sum of dp over all values ----------
    cout << query(1, 0, sz - 1, 0, sz - 1) % MOD << "\n";
    return 0;
}
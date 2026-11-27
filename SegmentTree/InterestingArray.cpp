#include <bits/stdc++.h>
using namespace std;

const int MAXBIT = 30;
int n, m;
vector<int> L, R, Q;   // constraints (0-indexed l, r)
vector<int> a;         // answer array
vector<int> t;         // segment tree storing AND

// Build segment tree: each node stores AND of its segment
void build(int node, int lo, int hi) {
    if (lo == hi) {
        t[node] = a[lo];
        return;
    }
    int mid = (lo + hi) / 2;
    build(2 * node, lo, mid);
    build(2 * node + 1, mid + 1, hi);
    t[node] = t[2 * node] & t[2 * node + 1];
}

// AND of range [l, r]
int query(int node, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return (1 << MAXBIT) - 1;  // identity for AND: all 1s
    if (l <= lo && hi <= r) return t[node];          // fully inside
    int mid = (lo + hi) / 2;
    return query(2 * node, lo, mid, l, r) &
           query(2 * node + 1, mid + 1, hi, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    L.resize(m); R.resize(m); Q.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> L[i] >> R[i] >> Q[i];
        L[i]--; R[i]--;                 // convert to 0-indexed
    }

    a.assign(n, 0);
    vector<int> sum(n + 1);             // difference array

    // ---------- STEP 1: construct the array ----------
    // Process each bit separately
    for (int bit = 0; bit < MAXBIT; bit++) {
        fill(sum.begin(), sum.end(), 0);    // reset diff array for this bit

        for (int i = 0; i < m; i++) {
            if ((Q[i] >> bit) & 1) {        // this constraint needs this bit set
                sum[L[i]]++;                // range starts: +1 at l
                sum[R[i] + 1]--;            // range ends: -1 at r+1
            }
        }

        for (int i = 0; i < n; i++) {
            if (i > 0) sum[i] += sum[i - 1];        // prefix sum -> coverage count
            if (sum[i] > 0) a[i] |= (1 << bit);     // covered by >=1 constraint -> set bit
        }
    }

    // ---------- STEP 2: validate the array ----------
    t.assign(4 * n, 0);
    build(1, 0, n - 1);

    for (int i = 0; i < m; i++) {
        int val = query(1, 0, n - 1, L[i], R[i]);
        if (val != Q[i]) {                  // AND has extra bits -> conflict
            cout << "NO\n";
            return 0;
        }
    }

    // ---------- all constraints satisfied ----------
    cout << "YES\n";
    for (int i = 0; i < n; i++) cout << a[i] << " ";
    cout << "\n";
    return 0;
}
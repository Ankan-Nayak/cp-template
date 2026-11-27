/*
=========================================================
PROBLEM (CSES 2206, Pizzeria Queries)
There are n buildings in a row. Building i has a pizzeria
with pizza price p_i. You get q queries of two types:
  1 k x : set p_k = x
  2 k   : you are at building k. Print the minimum cost of
          getting a pizza, where buying at building i costs
          p_i + |k - i| (the price plus the walking distance).

Example (my own):
  p = 3 8 5 2 7, query "2 2"
  i=1: 3+1=4, i=2: 8, i=3: 5+1=6, i=4: 2+2=4, i=5: 7+3=10
  Output: 4

STRATEGY
1. Remove the absolute value by splitting into two cases.
   Left side (i <= k):   cost = p_i + (k - i) = (p_i - i) + k
   Right side (i >= k):  cost = p_i + (i - k) = (p_i + i) - k
2. The k part is fixed for a query, so we only need the minimum of
   (p_i - i) over the left range and the minimum of (p_i + i)
   over the right range.
3. Build two segment trees BEFOREHAND (before reading queries):
     L tree stores p_i - i   (min over [1, k])
     R tree stores p_i + i   (min over [k, n])
4. Type 1: point update in both trees with the new p_k:
     L[k] = x - k,  R[k] = x + k
5. Type 2: answer = min( queryL(1, k) + k , queryR(k, n) - k )

Complexity: O(n + q log n)
=========================================================
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = LLONG_MAX / 4;   // identity for min (safe against overflow when adding k)

int n, q;
vector<ll> p;
vector<ll> L, R;                // L = min tree of (p_i - i), R = min tree of (p_i + i)

// Build both trees at once
void build(int idx, int l, int r) {
    if (l == r) {
        L[idx] = p[l] - l;      // left-side value
        R[idx] = p[l] + l;      // right-side value
        return;
    }
    int mid = (l + r) / 2;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    L[idx] = min(L[2 * idx], L[2 * idx + 1]);
    R[idx] = min(R[2 * idx], R[2 * idx + 1]);
}

// Point update: set p[pos] = val in both trees
void update(int idx, int l, int r, int pos, ll val) {
    if (l == r) {
        L[idx] = val - pos;
        R[idx] = val + pos;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * idx, l, mid, pos, val);
    else            update(2 * idx + 1, mid + 1, r, pos, val);
    L[idx] = min(L[2 * idx], L[2 * idx + 1]);
    R[idx] = min(R[2 * idx], R[2 * idx + 1]);
}

// Range min on the chosen tree (tree = L or R)
ll query(vector<ll> &tree, int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return INF;            // outside: identity for min
    if (ql <= l && r <= qr) return tree[idx];    // fully inside
    int mid = (l + r) / 2;
    return min(query(tree, 2 * idx, l, mid, ql, qr),
               query(tree, 2 * idx + 1, mid + 1, r, ql, qr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    p.resize(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];    // 1-indexed

    L.assign(4 * n, INF);
    R.assign(4 * n, INF);
    build(1, 1, n);                              // build before any query

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            ll x;
            cin >> k >> x;
            update(1, 1, n, k, x);               // update both trees
        } else {
            int k;
            cin >> k;
            ll left  = query(L, 1, 1, n, 1, k) + k;   // best pizzeria at i <= k
            ll right = query(R, 1, 1, n, k, n) - k;   // best pizzeria at i >= k
            cout << min(left, right) << "\n";
        }
    }
    return 0;
}
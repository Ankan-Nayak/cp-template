/*
=========================================================
PROBLEM (CSES 2166, Prefix Sum Queries)
Given an array of n integers and q queries of two types:
  1 k u : set a[k] = u
  2 a b : print the maximum prefix sum of the subarray a[a..b],
          i.e. max over i in [a, b] of (a[a] + a[a+1] + ... + a[i])

Example (my own):
  a = 1 2 -3 4, query "2 1 4"
  prefix sums: 1, 3, 0, 4  -> Output: 4

STRATEGY
1. Each segment tree node stores 2 values for its segment:
     sum  = total sum of the segment
     pref = best prefix sum of the segment (non-empty)
   (suff is NOT needed here. It was only needed for the max
    subarray problem, because a crossing subarray needs a
    suffix of L. Here every prefix starts at the left end.)
2. Merge left child L and right child R:
     sum  = L.sum + R.sum
     pref = max(L.pref, L.sum + R.pref)
       -> the prefix stops inside L, or takes all of L and continues into R
3. Leaf with value x: sum = x, pref = x.
   (Check the statement: if an empty prefix is allowed, use
    pref = max(0, x) at the leaf instead.)
4. Type 1: point update, recompute parents with merge.
5. Type 2: range query [a, b]. Combine the pieces from left to
   right with merge (order matters!) and print the result's pref.
   Out-of-range nodes return an identity node {sum = 0, pref = -INF},
   which never changes the answer.

Complexity: O(n + q log n)
=========================================================
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll NEG = LLONG_MIN / 4;   // -infinity that is safe to add sums to

struct Node {
    ll sum  = 0;     // sum of the entire segment
    ll pref = NEG;   // max prefix sum; default NEG makes Node() the identity
};

int n, q;
vector<ll> a;
vector<Node> t;

// Merge two adjacent segments (L is the left one, R is the right one)
Node merge(const Node &L, const Node &R) {
    Node res;
    res.sum  = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);   // stop in L, or all of L + prefix of R
    return res;
}

// Build a leaf from a single value
Node makeLeaf(ll x) {
    Node res;
    res.sum  = x;
    res.pref = x;    // non-empty prefix: use max(0, x) if empty is allowed
    return res;
}

void build(int idx, int l, int r) {
    if (l == r) {
        t[idx] = makeLeaf(a[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * idx, l, mid);
    build(2 * idx + 1, mid + 1, r);
    t[idx] = merge(t[2 * idx], t[2 * idx + 1]);
}

// Point update: a[pos] = val
void update(int idx, int l, int r, int pos, ll val) {
    if (l == r) {
        t[idx] = makeLeaf(val);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * idx, l, mid, pos, val);
    else            update(2 * idx + 1, mid + 1, r, pos, val);
    t[idx] = merge(t[2 * idx], t[2 * idx + 1]);
}

// Range query on [ql, qr]: returns the combined Node for that range
Node query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return Node();        // outside: identity {0, -INF}
    if (ql <= l && r <= qr) return t[idx];      // fully inside
    int mid = (l + r) / 2;
    // left part first, then right part (order matters for pref)
    return merge(query(2 * idx, l, mid, ql, qr),
                 query(2 * idx + 1, mid + 1, r, ql, qr));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    a.resize(n);
    for (auto &x : a) cin >> x;

    t.assign(4 * n, Node());
    build(1, 0, n - 1);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k;
            ll u;
            cin >> k >> u;
            update(1, 0, n - 1, k - 1, u);          // 0-indexed
        } else {
            int l, r;
            cin >> l >> r;
            Node res = query(1, 0, n - 1, l - 1, r - 1);
            cout << res.pref << "\n";               // best prefix of a[l..r]
        }
    }
    return 0;
}
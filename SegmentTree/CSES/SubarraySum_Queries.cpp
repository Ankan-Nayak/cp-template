/*
=========================================================
PROBLEM (CSES 1190, Subarray Sum Queries)
Given an array of n integers and q updates (k, x):
set a[k] = x, then print the maximum subarray sum
(an empty subarray is allowed, so the answer is at least 0).

Example:
  5 3
  1 2 -3 5 -1
  2 6
  3 1
  2 -2
  Output: 9 13 6

STRATEGY
1. Each segment tree node stores 4 values for its segment:
     sum  = total sum of the whole segment
     pref = best prefix sum (starts at the left end, empty allowed)
     suff = best suffix sum (ends at the right end, empty allowed)
     best = best subarray sum anywhere inside the segment
2. The best subarray of a merged segment [L | R] has 3 cases:
     a) fully inside L          -> L.best
     b) fully inside R          -> R.best
     c) crossing the middle     -> L.suff + R.pref
        (left part must touch the middle = suffix of L,
         right part must touch the middle = prefix of R,
         and the two choices are independent)
3. Merge rules:
     sum  = L.sum + R.sum
     pref = max(L.pref, L.sum + R.pref)   // stop inside L, or take all of L and go into R
     suff = max(R.suff, R.sum + L.suff)   // stay inside R, or take all of R and go into L
     best = max(L.best, R.best, L.suff + R.pref)
4. Leaf with value x: sum = x, pref = suff = best = max(0, x)
   (0 because the empty subarray is allowed).
5. For each update: change the leaf, recompute parents with merge,
   print root.best.

Dry run on [1 2 -3 5]:  L=[1,2] -> (sum 3, pref 3, suff 3, best 3)
                        R=[-3,5] -> (sum 2, pref 2, suff 5, best 5)
  merged: sum 5, pref max(3,3+2)=5, suff max(5,2+3)=5,
          best max(3,5,3+2)=5

Complexity: O(n + q log n)
=========================================================
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;   // sums can reach about 2e5 * 1e9

struct Node {
    ll sum  = 0;   // sum of the entire segment
    ll pref = 0;   // max prefix sum (empty allowed)
    ll suff = 0;   // max suffix sum (empty allowed)
    ll best = 0;   // max subarray sum (empty allowed)
};

int n, q;
vector<ll> a;
vector<Node> t;

// Merge two adjacent segments (L is the left one, R is the right one)
Node merge(const Node &L, const Node &R) {
    Node res;
    res.sum  = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);              // stop in L, or all of L + prefix of R
    res.suff = max(R.suff, R.sum + L.suff);              // stay in R, or all of R + suffix of L
    res.best = max({L.best, R.best, L.suff + R.pref});   // inside L, inside R, or crossing
    return res;
}

// Build a leaf node from a single value
Node makeLeaf(ll x) {
    Node res;
    res.sum  = x;
    res.pref = max(0LL, x);   // empty prefix allowed -> never below 0
    res.suff = max(0LL, x);
    res.best = max(0LL, x);
    return res;
}

// Build the tree over a[l..r]
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
        t[idx] = makeLeaf(val);               // replace the leaf
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * idx, l, mid, pos, val);
    else            update(2 * idx + 1, mid + 1, r, pos, val);
    t[idx] = merge(t[2 * idx], t[2 * idx + 1]);   // recompute after the child changed
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
        int k;
        ll x;
        cin >> k >> x;
        k--;                                   // convert to 0-indexed
        update(1, 0, n - 1, k, x);
        cout << t[1].best << "\n";             // root.best = max subarray sum of whole array
    }
    return 0;
}
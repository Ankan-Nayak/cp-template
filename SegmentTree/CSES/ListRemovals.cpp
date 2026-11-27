/*
=========================================================
PROBLEM (CSES 1749, List Removals)
Given a list of n numbers, then n positions p1..pn.
For each p_i, remove the element at position p_i of the
CURRENT list (1-indexed) and print it.

Example:
  5
  2 6 1 4 2
  3 1 3 1 1
  Output: 1 2 2 6 4

STRATEGY
1. Positions shift after every removal, so a plain array is
   too slow (O(n) per removal).
2. Build a segment tree where each leaf = 1 (element still
   present) and each node = count of remaining elements in
   its segment.
3. "Remove the k-th remaining element" = find the k-th leaf
   with value 1:
     - if k <= left child's count -> the answer is in the left child
     - else -> it is in the right child, and we OFFSET k by the
       left count: k = k - tree[left]. Inside the right child,
       the left part no longer counts, so we are looking for the
       (k - leftCount)-th element there.
4. At the leaf, set it to 0 (removed), return its original index,
   and recompute counts on the way back up.
5. Print a[index].

Complexity: O(n log n)
=========================================================
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;      // original values
vector<int> tree;   // tree[idx] = number of remaining elements in segment

// Build: every position starts as present (count 1)
void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = 1;                       // leaf: one element present
        return;
    }
    int mid = (l + r) / 2;
    build(2 * idx + 1, l, mid);
    build(2 * idx + 2, mid + 1, r);
    tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];   // total remaining
}

// Find the k-th remaining element, remove it, return its ORIGINAL index
int removeKth(int idx, int l, int r, int k) {
    if (l == r) {
        tree[idx] = 0;                       // mark as removed
        return l;                            // original position in a[]
    }
    int mid = (l + r) / 2;
    int res;

    if (k <= tree[2 * idx + 1]) {
        // k-th element lies in the left half
        res = removeKth(2 * idx + 1, l, mid, k);
    } else {
        // lies in the right half: skip the left half's count (offset)
        res = removeKth(2 * idx + 2, mid + 1, r, k - tree[2 * idx + 1]);
    }

    // update this node's count after the removal below
    tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for (auto &x : a) cin >> x;

    tree.assign(4 * n, 0);
    build(0, 0, n - 1);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;                            // position in the current list
        int pos = removeKth(0, 0, n - 1, p); // original index of that element
        cout << a[pos] << " ";
    }
    cout << "\n";
    return 0;
}
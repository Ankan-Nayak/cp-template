#include <bits/stdc++.h>
using namespace std;

vector<long long> arr, tree, max_tree;

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = arr[l];
        max_tree[idx] = arr[l];
        return;
    }

    int mid = (l + r) / 2;
    build(2 * idx + 1, l, mid);
    build(2 * idx + 2, mid + 1, r);

    tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    max_tree[idx] = max(max_tree[2 * idx + 1], max_tree[2 * idx + 2]);
}

// arr[pos] = x
void update_point(int idx, int l, int r, int pos, long long x) {
    if (l == r) {
        tree[idx] = x;
        max_tree[idx] = x;
        return;
    }

    int mid = (l + r) / 2;
    if (pos <= mid) {
        update_point(2 * idx + 1, l, mid, pos, x);
    } else {
        update_point(2 * idx + 2, mid + 1, r, pos, x);
    }

    tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    max_tree[idx] = max(max_tree[2 * idx + 1], max_tree[2 * idx + 2]);
}

// arr[i] %= x for every i in [ql, qr]
void update_mod(int idx, int l, int r, int ql, int qr, long long x) {
    // no overlap, or every element here is < x (mod changes nothing)
    if (l > qr || r < ql || max_tree[idx] < x) {
        return;
    }

    if (l == r) {                        // leaf: apply the mod
        tree[idx] %= x;
        max_tree[idx] = tree[idx];
        return;
    }

    int mid = (l + r) / 2;
    update_mod(2 * idx + 1, l, mid, ql, qr, x);
    update_mod(2 * idx + 2, mid + 1, r, ql, qr, x);

    tree[idx] = tree[2 * idx + 1] + tree[2 * idx + 2];
    max_tree[idx] = max(max_tree[2 * idx + 1], max_tree[2 * idx + 2]);
}

// sum of [ql, qr]
long long query(int idx, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return 0;
    if (l >= ql && r <= qr) return tree[idx];

    int mid = (l + r) / 2;
    return query(2 * idx + 1, l, mid, ql, qr) +
           query(2 * idx + 2, mid + 1, r, ql, qr);
}

int main() {
    int n, q;
    cin >> n >> q;

    arr.resize(n);
    for (auto &v : arr) cin >> v;

    tree.assign(4 * n, 0);
    max_tree.assign(4 * n, 0);
    build(0, 0, n - 1);

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {                 // 1 l r x : arr[i] %= x on [l, r]
            int l, r;
            long long x;
            cin >> l >> r >> x;
            update_mod(0, 0, n - 1, l, r, x);
        } else if (type == 2) {          // 2 pos x : arr[pos] = x
            int pos;
            long long x;
            cin >> pos >> x;
            update_point(0, 0, n - 1, pos, x);
        } else {                         // 3 l r : print sum of [l, r]
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n - 1, l, r) << "\n";
        }
    }
    return 0;
}
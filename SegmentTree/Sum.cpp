#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> arr, tree;

void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        arr[l] = val;
        tree[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(idx * 2 + 1, l, mid, pos, val);
    } else {
        update(idx * 2 + 2, mid + 1, r, pos, val);
    }
    tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
}

int query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return 0;
    if (ql >= l && qr <= r) return tree[idx];
    int mid = (l + r) / 2;
    int leftAns = query(idx * 2 + 1, l, mid, ql, qr);
    int rightAns = query(idx * 2 + 2, mid + 1, r, ql, qr);
    return tree[idx] = leftAns + rightAns;
}

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2 + 1, l, mid);
    build(idx * 2 + 2, mid + 1, r);
    tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    arr.resize(n+1, 0);
    tree.resize(4 * (n + 1), 0);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    build(1, 1, n);

    int tc;
    cin >> tc;
    while (tc--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r;
            cin >> l >> r;
            cout << query(1, 1, n, l, r) << endl;
        } else {
            int pos, val;
            cin >> pos >> val;
            update(1, 1, n, pos, val);
        }
    }

    return 0;
}
/*
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
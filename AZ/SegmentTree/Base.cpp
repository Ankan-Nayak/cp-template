/*Yash Puniya*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> tree;
vector<ll> arr;

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

ll query(int idx, int l, int r, int ql, int qr) {
    // if (ql > r || qr < l) return LLONG_MAX; -> min calc
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[idx];
    int mid = (l + r) / 2;
    ll leftRes = query(idx * 2 + 1, l, mid, ql, qr);
    ll rightRes = query(idx * 2 + 2, mid + 1, r, ql, qr);
    return leftRes + rightRes;
    // return min(leftRes, rightRes); -> min calc
}

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
    // tree[idx] = min(tree[idx * 2 + 1], tree[idx * 2 + 2]); -> min calc
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, q;
    cin >> n >> q;
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    tree.resize(4 * n, 0);
    build(0, 0, n-1);

    while (q--) {
        int op;
        cin >> op;

        if (op == 1) {
            int l, r;
            cin >> l >> r;
            cout << query(0, 0, n-1, l, r) << '\n';
        } 

        if (op == 2) {
            int pos, val;
            cin >> pos >> val;
            update(0, 0, n-1, pos, val);
        }
    }
    
    return 0;
}

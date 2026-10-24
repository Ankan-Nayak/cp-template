#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> arr;
vector<pair<int, int>> tree;

pair<int, int> merge(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return {a.first, a.second + b.second};
    else if (a.first > b.first) return b;
    else return a;
}

void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        arr[l] = val;
        tree[idx] = {val, 1};
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        update(idx * 2 + 1, l, mid, pos, val);
    } else {
        update(idx * 2 + 2, mid + 1, r, pos, val);
    }
    tree[idx] = merge(tree[idx * 2 + 1], tree[idx * 2 + 2]);
}

pair<int, int> query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || r < ql) return {LLONG_MAX, 0};
    if (l >= ql && r <= qr) return tree[idx];
    int mid = (l + r) / 2;
    auto leftAns = query(idx * 2 + 1, l, mid, ql, qr);
    auto rightAns = query(idx * 2 + 2, mid + 1, r, ql, qr);
    return merge(leftAns, rightAns);
}

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {arr[l], 1};
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2 + 1, l, mid);
    build(idx * 2 + 2, mid + 1, r);
    tree[idx] = merge(tree[idx * 2 + 1], tree[idx * 2 + 2]);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    arr.resize(n+1, 0);
    tree.resize(4 * (n + 1), {LLONG_MAX, 0});
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
            auto ans = query(1, 1, n, l, r);
            cout << ans.first << ' ' << ans.second << endl;
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
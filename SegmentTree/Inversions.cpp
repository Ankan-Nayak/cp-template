#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<int> arr;
vector<int> tree;

int query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && qr >= r) return tree[idx];
    int mid = (l + r) / 2;
    auto leftAns = query(idx * 2 + 1, l, mid, ql, qr);
    auto rightAns = query(idx * 2 + 2, mid + 1, r, ql, qr);
    return leftAns + rightAns;
}

void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        tree[idx] += val;
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
    tree.resize(4 * (n + 1));
    // build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    for (int i = 1; i <= n; ++i) {
        int val = 1, pos = arr[i];
        update(1, 1, n, pos, val);

        int ans = query(1, 1, n, arr[i] + 1, n);
        cout << ans << endl;
    }

   
    return 0;
}
/*
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */
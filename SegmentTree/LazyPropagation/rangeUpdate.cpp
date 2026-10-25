/*
rather than updating points
update the range (l,r)

postpone operation
create another extra tree
apply
push in lazy tree (left and right)

10 
/\.    ->     0
             / \
            /.  \
            5.   5
*/


#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;
int arr[MAXN];
long long segTree[4 * MAXN], lazy[4 * MAXN];

void build(int idx, int l, int r) {
    if (l == r) {
        segTree[idx] = arr[l];
        return;
    }

    int mid = (l + r) / 2;

    build(2 * idx + 1, l, mid);
    build(2 * idx + 2, mid + 1, r);

    segTree[idx] = segTree[2 * idx + 1]
                 + segTree[2 * idx + 2];
}

void push(int idx, int l, int r) {
    if (lazy[idx] != 0) {
        segTree[idx] += lazy[idx] * (r - l + 1);

        if (l != r) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }

        lazy[idx] = 0;
    }
}

void update(int idx, int l, int r,
            int ql, int qr, long long val) {
    push(idx, l, r);

    if (l > qr || r < ql)
        return;

    if (l >= ql && r <= qr) {
        lazy[idx] += val;
        push(idx, l, r);
        return;
    }

    int mid = (l + r) / 2;

    update(2 * idx + 1, l, mid, ql, qr, val);
    update(2 * idx + 2, mid + 1, r, ql, qr, val);

    segTree[idx] = segTree[2 * idx + 1]
                 + segTree[2 * idx + 2];
}

long long query(int idx, int l, int r, int ql, int qr) {
    push(idx, l, r);

    if (l > qr || r < ql)
        return 0;

    if (l >= ql && r <= qr)
        return segTree[idx];

    int mid = (l + r) / 2;

    return query(2 * idx + 1, l, mid, ql, qr)
         + query(2 * idx + 2, mid + 1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    build(0, 0, n - 1);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r;
            long long val;
            cin >> l >> r >> val;

            update(0, 0, n - 1, l, r, val);
        } else {
            int l, r;
            cin >> l >> r;

            cout << query(0, 0, n - 1, l, r) << '\n';
        }
    }

    return 0;
}

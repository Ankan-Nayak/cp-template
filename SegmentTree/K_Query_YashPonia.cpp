
#include <bits/stdc++.h>
using namespace std;

#define int long long

vector<vector<int>> tree;
vector<int> employee, arr;

vector<int> merge(vector<int>& left, vector<int>& right) {
    vector<int> res;
    int i = 0, j = 0;

    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            res.push_back(left[i]);
            i++;
        } else {
            res.push_back(right[j]);
            j++;
        }
    }

    while (i < left.size()) {
        res.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        res.push_back(right[j]);
        j++;
    }

    return res;
}
void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {arr[l]};
        return;
    }

    int mid = (l + r) / 2;

    build(idx * 2 + 1, l, mid);
    build(idx * 2 + 2, mid + 1, r);

    tree[idx] = merge(tree[idx * 2 + 1],
                      tree[idx * 2 + 2]);
}

int query(int idx, int l, int r,
          int ql, int qr, int k) {
    // No overlap
    if (qr < l || ql > r) return 0;

    // Complete overlap
    if (ql <= l && r <= qr) {
        int total = tree[idx].size();

        int notGreater =
            upper_bound(tree[idx].begin(),
                        tree[idx].end(), k)
            - tree[idx].begin();

        return total - notGreater;
    }

    // Partial overlap
    int mid = (l + r) / 2;

    return query(idx * 2 + 1, l, mid, ql, qr, k)
         + query(idx * 2 + 2, mid + 1, r, ql, qr, k);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    arr.resize(n + 1);
    tree.resize(4 * n);

    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
    }

    build(0, 1, n);

    while (q--) {
        int l, r, k;
        cin >> l >> r >> k;

        cout << query(0, 1, n, l, r, k) << '\n';
    }

    return 0;
}

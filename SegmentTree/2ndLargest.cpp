
#include <bits/stdc++.h>
using namespace std;

#define int long long

struct DS{
    pair<int, int> a;
    pair<int, int> b;
};

vector<DS> tree;
vector<int> arr;

DS merge(DS left, DS right) {
    map<int, int, greater<int>> mp;

    mp[left.a.first] += left.a.second;
    mp[left.b.first] += left.b.second;
    mp[right.a.first] += right.a.second;
    mp[right.b.first] += right.b.second;

    vector<pair<int, int>> v;

    for (auto it : mp) {
        if (it.first != 0 && it.second > 0) {
            v.push_back(it);
        }
    }

    DS res = {{0, 0}, {0, 0}};

    if (v.size() >= 1) res.a = v[0];
    if (v.size() >= 2) res.b = v[1];

    return res;
}
void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        arr[l] = val;
        tree[idx] = {{val, 1}, {0, 0}};
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

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {{arr[l], 1}, {0, 0}};
        return;
    }
    int mid = (l + r) / 2;
    build(idx * 2 + 1, l, mid);
    build(idx * 2 + 2, mid + 1, r);
    tree[idx] = merge(tree[idx * 2 + 1], tree[idx * 2 + 2]);
}

DS query(int idx, int l, int r, int ql, int qr) {
    if (l > qr || r < ql) return {{0,0}, {0,0}};
    if (l >= ql && r <= qr) return tree[idx];
    int mid = (l + r) / 2;
    DS left = query(idx * 2 + 1, l, mid, ql, qr);
    DS right = query(idx * 2 + 2, mid + 1, r, ql, qr);
    return merge (left, right);
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

    build(1, 1, n);



    while (q--) {
        int type, x, y;
        cin >> type >> x >> y;

        if (type == 1) {
            update(1, 1, n, x, y);
        }
        else {
            DS it = query(1, 1, n, x, y);
            cout << it.b.first << ' ' << it.b.second << '\n';
        }
    }

    

    return 0;
}

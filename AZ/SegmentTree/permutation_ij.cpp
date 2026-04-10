#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<int> tree;

// update: mark value as seen
void update(int idx, int l, int r, int pos) {
    if (l == r) {
        tree[idx] = 1;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2*idx+1, l, mid, pos);
    else update(2*idx+2, mid+1, r, pos);

    tree[idx] = tree[2*idx+1] + tree[2*idx+2];
}

// query: count in range
int query(int idx, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return tree[idx];

    int mid = (l + r) / 2;
    return query(2*idx+1, l, mid, ql, qr) +
           query(2*idx+2, mid+1, r, ql, qr);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    tree.resize(4*n, 0);

    for (int i = 0; i < n; i++) {
        // count elements > a[i]
        int cnt = query(0, 1, n, a[i]+1, n);
        cout << cnt << " ";

        // mark current element
        update(0, 1, n, a[i]);
    }

    return 0;
}


/*
Problem Statement (your words → formal)
👉 Given a permutation a[0..n-1]
For each index i, compute:
count of j < i such that a[j] > a[i]
👉 And print this for every i
*/
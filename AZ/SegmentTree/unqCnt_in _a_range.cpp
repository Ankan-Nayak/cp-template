#include<bits/stdc++.h>
using namespace std;

#define ll long long

vector<ll> tree;

// update position → mark 1 or 0
void update(int idx, int l, int r, int pos, int val) {
    if (l == r) {
        tree[idx] = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2*idx+1, l, mid, pos, val);
    else update(2*idx+2, mid+1, r, pos, val);

    tree[idx] = tree[2*idx+1] + tree[2*idx+2];
}

// range sum query
ll query(int idx, int l, int r, int ql, int qr) {
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

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    int q;
    cin >> q;

    vector<vector<pair<int,int>>> queries(n); 
    // queries[r] = list of (l, query_id)

    vector<int> ans(q);

    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        queries[r].push_back({l, i});
    }

    tree.resize(4*n, 0);

    unordered_map<int,int> last;

    for (int i = 0; i < n; i++) {

        // remove previous occurrence
        if (last.count(arr[i])) {
            update(0, 0, n-1, last[arr[i]], 0);
        }

        // mark current position
        update(0, 0, n-1, i, 1);
        last[arr[i]] = i;

        // answer queries ending at i
        for (auto [l, id] : queries[i]) {
            ans[id] = query(0, 0, n-1, l, i);
        }
    }

    for (int x : ans) cout << x << "\n";

    return 0;
}

/*
Q. How many elements have their "LAST occurrence" inside [l, r]
At any time:
Only LAST occurrences have value = 1
Rest = 0
Range sum query → how many 1's in [l, r]
tree[j] = 1  → if j is the LAST occurrence of some element till i  
tree[j] = 0  → otherwise

we have calculated  -> Which indices are LAST occurrences up to r
during query all mark < l, don't take those i in some, return 0 (prunning)

*/
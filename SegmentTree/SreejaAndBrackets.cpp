#include <bits/stdc++.h>
using namespace std;

// Node stores info about one segment
struct Node {
    int matched = 0;  // number of matched pairs "()" inside segment
    int open = 0;     // unmatched '(' left over
    int close = 0;    // unmatched ')' left over
};

string s;
vector<Node> t;

// Merge two adjacent segments (a is left, b is right)
Node merge(const Node &a, const Node &b) {
    Node res;
    int x = min(a.open, b.close);          // new pairs: a's '(' with b's ')'
    res.matched = a.matched + b.matched + x;
    res.open    = a.open + b.open - x;     // '(' that stayed unmatched
    res.close   = a.close + b.close - x;   // ')' that stayed unmatched
    return res;
}

void build(int node, int lo, int hi) {
    if (lo == hi) {
        // leaf: a single bracket
        if (s[lo] == '(') t[node].open = 1;
        else              t[node].close = 1;
        return;
    }
    int mid = (lo + hi) / 2;
    build(2 * node, lo, mid);
    build(2 * node + 1, mid + 1, hi);
    t[node] = merge(t[2 * node], t[2 * node + 1]);
}

Node query(int node, int lo, int hi, int l, int r) {
    if (r < lo || hi < l) return Node();   // outside: empty node {0,0,0} is the identity
    if (l <= lo && hi <= r) return t[node]; // fully inside
    int mid = (lo + hi) / 2;
    // order matters: left result must be merged first, then right
    return merge(query(2 * node, lo, mid, l, r),
                 query(2 * node + 1, mid + 1, hi, l, r));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = s.size();
    t.assign(4 * n, Node());
    build(1, 0, n - 1);

    int m;
    cin >> m;
    while (m--) {
        int l, r;
        cin >> l >> r;
        l--; r--;                           // convert to 0-indexed
        Node ans = query(1, 0, n - 1, l, r);
        cout << ans.matched * 2 << "\n";    // each pair = 2 characters
    }
    return 0;
}
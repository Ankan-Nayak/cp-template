#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

vector<int> a, subseq;

void rec(int idx) {
    if (idx == a.size()) {
        for (auto it : subseq) cout << it << ' ';
        cout << '\n';
        return;
    }
    // take element
    subseq.push_back(a[idx]);
    rec(idx + 1);
    subseq.pop_back();
    

    // don't take element
    rec(idx + 1);
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    rec(0);
    return 0;
}

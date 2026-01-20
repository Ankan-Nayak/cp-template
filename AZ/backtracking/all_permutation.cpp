#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

int n;
map<int, int> mp;
vector<int> cur_permutation;

void rec(int level) {
    if (level == n) {
        for (auto it : cur_permutation) cout << it << ' ';
        cout << '\n';
        return;
    }

    for (auto &v : mp) {
        if (v.second > 0) {
            v.second--;
            cur_permutation.push_back(v.first);

            rec(level + 1);

            cur_permutation.pop_back();
            v.second++;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        mp[x]++;
    }
    
    rec(0);

    return 0;
}
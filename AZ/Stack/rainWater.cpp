#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n + 1), left(n + 2), right(n + 2, 0);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
            left[i] = max(left[i - 1], a[i]);
        }
        for (int i = n; i >= 1; --i) {
            right[i] = max(right[i + 1], a[i]);
        }

        int water = 0;
        for (int i = 1; i <= n; ++i) {
            water += max(0LL, min(left[i - 1], right[i + 1]) - a[i]);
        }
        cout << water << endl;
    }

    return 0;
}

// Golden Rules
/*
    Solutions are simple.
 
    Proofs are simple.
 
    Implementations are simple.
*/
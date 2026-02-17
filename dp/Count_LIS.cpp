#include<bits/stdc++.h>
using namespace std;

#define int long long
const int M=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        
        vector<int> len(n + 1, 1); // LIS ending at i
        vector<int> cnt(n + 1, 1); // no of LIS ending at i

        
        
        int mx_len = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (a[i] > a[j]) {
                    if (len[j] + 1 > len[i]) {
                        len[i] = len[j] + 1;
                        cnt[i] = cnt[j];
                    }
                    else if (len[j] + 1 == len[i]) {
                        cnt[i] += cnt[j];
                        cnt[i] %= M;
                    }
                }
            }
            mx_len = max(mx_len, len[i]); // length of LIS
        }

        int res = 0;
        for (int i = 1; i <= n; ++i) {
            if (len[i] == mx_len) (res += cnt[i]) %= M;
        }

        cout << res << endl;
    }
    return 0;
}


// For LIS use Iterative only
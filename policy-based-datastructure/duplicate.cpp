
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long

#define ordered_multiset tree<pair<int,int>, null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> details(n + 1, 0);

    ordered_multiset ms;
    int id = 1;

    for (int i = 1; i <= n; ++i) {
        cin >> details[i];
        ms.insert({details[i], i});
    }

    while (q--) {
        char ch;
        int a, b;
        cin >> ch >> a >> b;
        
        if (ch == '!') {
            // Delete one occurrence of x
            auto it = ms.lower_bound({details[a], a});

            ms.erase(it);

            details[a] = b;
            ms.insert({b, a});
        } 

        else {
            if (a > b) swap(a, b);
            cout << ms.order_of_key({b+1, LLONG_MIN}) - ms.order_of_key({a, LLONG_MIN}) << endl;
        }
    }

    return 0;
}

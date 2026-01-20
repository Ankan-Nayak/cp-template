#include <bits/stdc++.h>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

int n, k;
vector<int> kth_p;

signed main() {
    ordered_set o_set;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        o_set.insert(i);
    }

    // if ceil k / (sz - 1)) ! = x, put x th value in the pos
    // now k = k % (sz - 1)); sz -= 1
    for (int i = 1; i < n - 13; ++i) {
        kth_p.push_back(i);
        o_set.erase(i);
    }
    

    while (k > 0 && kth_p.size() < n  &&  o_set.size() > 0) {
        int sz = o_set.size();

        int fact = 1;
        for (int i = 1; i <= sz - 1; ++i) fact *= i;

        int idx = (k + fact - 1) / fact;

        // cout << "idx " << idx << endl;

        int nth_idx_val = *(o_set.find_by_order(idx - 1)); 
        kth_p.push_back(nth_idx_val);

        // cout << "nth_idx_val " << nth_idx_val << endl;

        k -= fact * (idx - 1);

        // cout << "k " << k << endl;

        if (o_set.find(nth_idx_val) != o_set.end()) {
            o_set.erase(o_set.find(nth_idx_val));
        }
    }

    for (auto it : o_set) kth_p.push_back(it);

    for (auto it : kth_p) cout << it << ' ';

   
    return 0;
}
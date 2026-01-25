/*
Problem Statement:
You are given an array a of n positive integers, where a[i] represents the amount of work.
The work must be assigned in order to k persons such that each person gets a contiguous
sequence of work.

Each person can handle at most some maximum workload.
Find the minimum possible value of this maximum workload so that all work is assigned
using at most k persons.
*/




#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        auto check = [&](int mid)->bool {
            int person = 1, work = 0;
            for (int i = 0; i < n; ++i) {
                if (work + a[i] <= mid) work += a[i];
                else {
                    work = a[i];
                    person += 1;
                }
            }
            return person <= k;
        };

        // don't use random
        int low = *max_element(a.begin(), a.end()); // use low according to Q
        int high = accumulate(a.begin(), a.end(), 0LL); // use high according to Q
        int ans = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}




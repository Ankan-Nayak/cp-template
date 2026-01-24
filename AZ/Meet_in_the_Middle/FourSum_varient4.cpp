#include <bits/stdc++.h>
using namespace std;

/*
VARIANT 4:
----------
Question:
Count number of quadruples (a, b, c, d) such that:
Arr[a] + Arr[b] + Arr[c] + Arr[d] == TARGET

Idea:
-----
Instead of boolean or index,
store count of (c, d) pairs.

pos[sum] = number of times (c,d) gives this sum
*/

long long is4SUMpossible(vector<int>& arr, int n, int target) {

    long long ans = 0;
    map<int, int> pos;

    for (int b = n - 2; b >= 1; b--) {

        for (int a = b - 1; a >= 0; a--) {
            int need = target - arr[a] - arr[b];
            ans += pos[need]; // add all matching (c,d)
        }

        int c = b;
        for (int d = c + 1; d < n; d++) {
            pos[arr[c] + arr[d]]++;
        }
    }

    return ans;
}

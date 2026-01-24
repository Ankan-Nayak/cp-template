#include <bits/stdc++.h>
using namespace std;

/*
VARIANT 3:
----------
Question:
Find one quadruple (a, b, c, d) such that:
Arr[a] + Arr[b] + Arr[c] + Arr[d] == TARGET

Return indices (a, b, c, d)

Idea:
-----
Store sum of (c, d) → indices.
Then try all (a, b) and check complement.

pos[sum] = {c, d}
*/

vector<int> is4SUMpossible(vector<int>& arr, int n, int target) {

    map<int, pair<int,int>> pos;

    for (int b = n - 2; b >= 1; b--) {

        for (int a = b - 1; a >= 0; a--) {
            int need = target - arr[a] - arr[b];
            if (pos.count(need)) {
                auto cd = pos[need];
                return {a, b, cd.first, cd.second};
            }
        }

        int c = b;
        for (int d = c + 1; d < n; d++) {
            pos[arr[c] + arr[d]] = {c, d};
        }
    }

    return {}; // no solution
}

// ### Problem Statement

// You have **N bricks** in a line and **M colors**. Color the bricks such that there are exactly **K positions** where adjacent bricks have different colors. Count the number of valid colorings modulo \(10^9+7\).

// ### Constraints

// * 100 test case
// * \(1 \le N,M \le 2000\)
// * \(0 \le K \le N-1\)


#include <bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 2005;
const int MOD = 1e9 + 7;

int n, m, k;
int dp[MAXN][MAXN];

// rec(level, prev color, segment) won't work
int rec(int level, int segment) {

    if (segment > k)
        return 0;

    if (level == n + 1)
        return (segment == k);

    if (dp[level][segment] != -1)
        return dp[level][segment];

    // Same color -> segment stays same
    // Different color -> segment increases by 1, (m-1) choices
    int ans = rec(level + 1, segment);

    ans = (ans + (m - 1) * rec(level + 1, segment + 1)) % MOD;

    return dp[level][segment] = ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        cin >> n >> m >> k;

        memset(dp, -1, sizeof(dp)); // mandatory to use -> reason below

        // First brick: m choices
        cout << (m * rec(1, 0)) % MOD << '\n';
    }

    return 0;
}

/*
If some input value changes between test cases, and that value affects your recurrence, 
you cannot reuse the old dp values unless you reset/recompute the DP appropriately.
Test case 1:
n = 3
a = {1, 2, 3}
target = 5

Test case 2:
n = 3
a = {10, 20, 30}
target = 5

The state:

rec(2, 5)

looks identical in both test cases.

But it actually means different things because a[] is different.

Test case 1
rec(2, 5)

means:

Can I make 5 using {2, 3}?

Test case 2
rec(2, 5)

means:

Can I make 5 using {20, 30}?

The answer can clearly be different.

Therefore, if you kept:

dp[2][5]

from Test Case 1, you cannot use it for Test Case 2.




but the answer actually depends on:

idx
left
a[]
*/
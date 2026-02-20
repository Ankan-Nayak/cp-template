/*
_ _ _ _ _ _ 
_ _ mid _ _ _ 
which mid to split ans solve the problem
*/

#include<bits/stdc++.h>
using namespace std;

int n;
int x[100];
int dp[100][100];

int rec(int l, int r) {
    if (l+1 == r) return 0;
    if (dp[l][r] != -1) return dp[l][r];
    int ans = 1e9;
    for (int p = l+1; p <= r-1; ++p) {
        ans = min(ans, x[r] - x[l] + rec(l, p) + rec(p, r));
    }
    return dp[l][r] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i];
    }
    x[0] = 0;

    memset(dp, -1, sizeof(dp));
    cout << rec(0, n);
    return 0;
}


// dp(l,r) = (x[r]-x[l]) + dp(l,p) + dp(p,r) -> 0(n^2)
// to find the optimal p use loop from [l,r] -> 0(n)

// TC -> 0(n^3)

/*
Problem: Minimum Cost to Cut a Rod

You are given a rod of length L and N cut positions along the rod.
Each cut must be performed at one of the given positions.

When you cut a rod, the cost of making the cut equals the length of
the current rod segment being cut.

After a cut, the rod is split into two smaller segments, which can
be cut independently.

Your task is to determine the minimum total cost required to perform
all cuts.

Input:
- An integer L (length of the rod)
- An integer N (number of cuts)
- N integers representing cut positions (0 < cuts < L)

Output:
- Minimum total cost to complete all cuts

*/
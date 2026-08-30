// Given a sequence of N numbers, in one operation you can remove any contiguous palindromic subsequence. After removal, the remaining elements join together.

// Find the minimum number of operations needed to remove all elements.



#include <bits/stdc++.h>
using namespace std;

int n;
int a[505];
int memo[505][505];

int solve(int l, int r) {
    if (l > r) return 0;
    if (l == r) return 1;
    if (memo[l][r] != -1) return memo[l][r];

    // Option 1: remove a[l] by itself
    int res = solve(l + 1, r) + 1;

    // Option 2: a[l] and a[l+1] are equal — remove them together (+1),
    // then clear the rest
    if (a[l] == a[l + 1]) {
        res = min(res, solve(l + 2, r) + 1);
    }

    // Option 3: a[l] matches some a[k], k >= l+2 — clear the middle,
    // then a[l] and a[k] merge into that removal for free
    for (int k = l + 2; k <= r; k++) {
        if (a[k] == a[l]) {
            res = min(res, solve(l + 1, k - 1) + solve(k + 1, r));
        }
    }

    return memo[l][r] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    memset(memo, -1, sizeof(memo));

    cout << solve(0, n - 1) << "\n";

    return 0;
}
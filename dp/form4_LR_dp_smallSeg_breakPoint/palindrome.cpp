#include <bits/stdc++.h>
using namespace std;

int n;
int a[505];
int dp[505][505];

int rec(int l, int r) {

    if (l > r)
        return 0;

    if (l == r)
        return 1;

    if (dp[l][r] != -1)
        return dp[l][r];

    // Delete a[l] separately
    int ans = 1 + rec(l + 1, r);

    // Try to connect a[l] with a[k]
    for (int k = l + 1; k <= r; k++) {

        if (a[l] == a[k]) {

            ans = min(ans,
                      rec(l + 1, k - 1)
                    + rec(k, r));
        }
    }

    return dp[l][r] = ans;
}

int main() {

    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    memset(dp, -1, sizeof(dp));

    cout << rec(0, n - 1) << '\n';

    return 0;
}
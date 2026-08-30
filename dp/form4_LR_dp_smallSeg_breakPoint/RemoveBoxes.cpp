## Remove Marbles — This is the classic "Remove Boxes" DP problem

Looking at your notes, the recursion state `Dp(l, r, k)` you've written matches this exactly:
- `l, r` = current subarray boundaries (left and right index)
- `k` = number of extra marbles of the **same color as `arr[l]`** that are already attached to the left of `l` (from marbles removed earlier that exposed a same-colored group)

### Full C++ Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int n;
int arr[105];
int dp[105][105][105]; // dp[l][r][k]

int solve(int l, int r, int k) {
    if (l > r) return 0;                    // no marbles left -> 0 points
    if (dp[l][r][k] != -1) return dp[l][r][k];

    int origL = l, origK = k;

    // Step 1: merge marbles equal to arr[l] that sit right next to it
    // (they behave like "attached" extra copies of arr[l])
    while (l + 1 <= r && arr[l + 1] == arr[l]) {
        l++;
        k++;
    }

    // Choice 1: remove this whole block (k+1 marbles of same color) right now
    int res = (k + 1) * (k + 1) + solve(l + 1, r, 0);

    // Choice 2: don't remove yet — skip ahead to some m > l with arr[m] == arr[l],
    // clear out everything between them first, then merge block[l] with block[m]
    for (int m = l + 1; m <= r; m++) {
        if (arr[m] == arr[l]) {
            res = max(res, solve(l + 1, m - 1, 0) + solve(m, r, k + 1));
        }
    }

    return dp[origL][r][origK] = res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) cin >> arr[i];

    memset(dp, -1, sizeof(dp));

    cout << solve(0, n - 1, 0) << "\n";
    return 0;
}
```

### Why the recursion works

**The trick:** removing marbles greedily (always take the biggest same-color group) doesn't give the max score, because sometimes it's better to *save* a color, clear out marbles in between, and let two separated same-colored groups merge into one bigger (and more valuable, since score is `k²`) group later.

**State:** `dp(l, r, k)` = max points obtainable from marbles in range `[l, r]`, given that `k` extra marbles of `arr[l]`'s color are "waiting" just to the left, ready to merge in.

At each call, two options are compared (matches your `Dp(4,3,0)` and `Dp(4,5,0)+Dp(7,3,2)` branches in the photo):

1. **Remove now:** Take the whole current same-colored block (size `k+1` after merging adjacent duplicates) and score `(k+1)²`, then solve the rest: `solve(l+1, r, 0)`.

2. **Wait and merge:** For every future index `m` in `(l, r]` where `arr[m] == arr[l]`, first clear out the "gap" between them (`solve(l+1, m-1, 0)`), then treat `arr[l]`'s block as `k+1` marbles now sitting next to `arr[m]`: `solve(m, r, k+1)`.

Take the max of all these — that's exactly the `2²` and `+12²` style annotations in your notes (scores accumulate as squares of merged block sizes).

**Base case:** `l > r` → empty range → 0 points.

### Complexity
- States: `O(n³)` (for `l, r, k`)
- Transition: `O(n)` loop for choice 2
- Total: `O(n⁴)` time, `O(n³)` space — with `n ≤ 100` this comfortably fits in 2 seconds.
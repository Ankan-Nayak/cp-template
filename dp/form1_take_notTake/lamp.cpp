


/*
**Streetlamps With Generator Truck — short version**

A dead-end road has posts `1..N`. A lamp on post `i` lights posts `i-1, i, i+1`. Every post must end up lit.

- Posts are `'L'` (live — can hold a lamp) or `'D'` (dead — can't hold a lamp, but still needs to be lit by a neighbor's lamp or the truck).
- You also have **one optional generator truck** you can park at any single post (live or dead) — it lights that post and its two neighbors too, for free (doesn't count as a lamp).

**Input:** `N`, then a string `z` of length `N` (`'L'`/`'D'`).
**Output:** minimum number of lamps needed to light every post, or `-1` if it's impossible even with the truck.

**Constraints:** `1 ≤ N ≤ 100,000`.
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int INF = 1e18;

int n;
string s;
int a[100005];
int dp[100005][2][2][2];
// dp[i][prevLit][curLit][truckUsed]
// prevLit   : is post i-1 already lit?  (false => post i MUST act now)
// curLit    : is post i already lit, because i-1 placed something there?
// truckUsed : has the (single) generator already been used?

int rec(int i, int prevLit, int curLit, int truckUsed) {
    if (i > n) return prevLit ? 0 : INF;     // last post must end up lit

    int &memo = dp[i][prevLit][curLit][truckUsed];
    if (memo != -1) return memo;

    int ans = INF;

    // A) put a lamp on post i (only if live)
    if (a[i] == 1)
        ans = min(ans, 1 + rec(i + 1, 1, 1, truckUsed));

    // B) park the generator on post i (live or dead, at most once)
    if (!truckUsed)
        ans = min(ans, rec(i + 1, 1, 1, 1));

    // C) do nothing -- only legal if i-1 didn't need i to save it
    if (prevLit)
        ans = min(ans, rec(i + 1, curLit, 0, truckUsed));

    return memo = ans;
}

signed main() {
    cin >> n >> s;
    for (int i = 1; i <= n; ++i) a[i] = (s[i - 1] == 'L') ? 1 : 0;

    memset(dp, -1, sizeof(dp));
    int ans = rec(1, 1, 0, 0);      // "post 0" is vacuously fine, post 1 not yet lit, truck unused
    cout << (ans >= INF ? -1 : ans) << endl;
}
/*
Subtraction Game (Power of Two Moves)

There are X chips in a pile. Two players play alternately. In one move, a player may remove Y chips,
where Y must be a power of two (Y = 2^m for some m ≥ 0) and Y ≤ remaining chips.
The player who cannot make a move loses.

Goal:
Given X, determine whether the starting player is in a winning or losing position assuming optimal play.

State Transition (DP intuition):
dp[x] depends on dp[x - 1], dp[x - 2], dp[x - 4], dp[x - 8], ... for all 2^m ≤ x.

Example:
Input: X = 6

Possible moves from 6:
- Remove 1 → state 5
- Remove 2 → state 4
- Remove 4 → state 2

If any reachable state is losing, then 6 is winning.
*/


#include<bits/stdc++.h>
using namespace std;

int n;
int dp[1000];

int rec(int x) {
    // pruning
    // Once we find a winning move, no need to test others.
    // Without pruning → extra useless recursion.

    // Lose state
    if (x == 0) {
        return 0; // can't make a move
    }

    // cache check
    if (dp[x] != -1) {
        return dp[x];
    }

    // compute
    int ans = 0;
    for (int m = 0; (1<<m) <= x; ++m) {
        if (rec(x - (1<<m)) == 0) {
            ans = 1;
            break;  // ← THIS is pruning
        }
    }

    // save and return
    return dp[x] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n;
    memset(dp, -1, sizeof(dp));
    cout << rec(n);

    // or  observe pattern

    for (int i = 0; i <= 100; ++i) cout << i << ' ' << rec(i) << endl; // observe pattern
    if (n % 3 == 0) {
        cout << "Lose";
    } else {
        cout << "Win";
    }

    
    return 0;
}




// pull dp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, 0);  // dp[x] = 0 lose, 1 win
    dp[0] = 0;

    for (int x = 1; x <= n; ++x) {
        dp[x] = 0;  // assume losing

        for (int m = 0; (1 << m) <= x; ++m) {
            if (dp[x - (1 << m)] == 0) {
                dp[x] = 1;      // winning state
                break;          // pruning
            }
        }
    }

    cout << dp[n] << endl;
}





// push dp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> dp(n + 1, -1);
    dp[0] = 0;   // losing base state

    for (int x = 0; x <= n; ++x) {

        // If state not yet decided, skip
        if (dp[x] == -1) continue;

        // Only propagate from losing states
        if (dp[x] == 0) {

            for (int m = 0; x + (1 << m) <= n; ++m) {
                dp[x + (1 << m)] = 1;   // reachable → winning
            }
        }
    }

    // Any unmarked state is losing
    for (int x = 0; x <= n; ++x) {
        if (dp[x] == -1) dp[x] = 0;
    }

    cout << dp[n] << endl;
}
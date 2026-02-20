#include<bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a, dp;

int rec(int x) {
    if (x == 0) return 0;
    if (dp[x] != -1) return dp[x];
    int ans= 0;
    for (int j = 1; j <= n; ++j) {
        if (x - a[j] >= 0  &&  rec(x - a[j]) == 0)  {
            ans = 1;
            break;
        }
    }
    return dp[x] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, k;
    a.resize(n+1);
    dp.resize(k+1, -1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    cout << ((rec(k) == 1) ? "First" : "Second");
    return 0;
}





#include<bits/stdc++.h>
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1), dp(k + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    dp[0] = 0; // lose
    for (int i = 1; i <= k; ++i) { 
        for (int j = 1; j <= n; ++j) {
            if (i >= a[j] && dp[i - a[j]] == 0) dp[i] = 1;
        }
    }
    cout << ((dp[k] == 1) ? "First" : "Second");
    return 0;
}


/*
Stone Removal Game (Subtraction Game)

Problem Statement:
There are K stones in a pile. Two players (First and Second) play alternately.
A set A = {a1, a2, ..., aN} is given. In one move, a player may remove
exactly ai stones (for any ai ∈ A) if enough stones remain.
A player who cannot make a move loses.
Assuming optimal play, determine the winner.

DP State:
dp[x] = 1 → winning position with x stones
dp[x] = 0 → losing position with x stones

Base Case:
dp[0] = 0   (no stones → no move → losing)

Transition Logic:
For each x from 1 to K:
    dp[x] = 0 (assume losing)
    For each move ai in A:
        If x - ai ≥ 0 and dp[x - ai] == 0:
            dp[x] = 1   (can force opponent lose)
            break

Result:
If dp[K] == 1 → First wins
Else → Second wins
*/
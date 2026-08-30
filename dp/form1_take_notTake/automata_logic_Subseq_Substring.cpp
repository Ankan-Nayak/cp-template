/*
    Problem:
    Count binary strings of length N that DO NOT contain "0100"
    as a substring.


    AUTOMATON / PREFIX MATCHING
    ---------------------------

    match = how many characters of the pattern "0100"
            are currently matched as a suffix.

    Pattern:
             0 1 0 0
             ────────
    match:   0 1 2 3 4

    States:

        match = 0 : ""
        match = 1 : "0"
        match = 2 : "01"
        match = 3 : "010"
        match = 4 : "0100"  -> FOUND -> INVALID


    TRANSITION DIAGRAM
    ------------------

                    1
               ┌─────────┐
               │         ↓
             [0] --0--> [1]
                         ││
                       0 ││ 1
                         ↓↓
                        [1][2]

    More clearly:

                 1
             ┌───────┐
             │       ↓
             0 --0-> 1 --1-> 2
             ↑       │       │
             │       0       0
             │       ↓       ↓
             └-------1       3
                             ││
                           1 ││ 0
                             ↓↓
                             2  4

    Exact transitions:

    state 0:
        append 0 -> state 1
        append 1 -> state 0

    state 1: currently matched "0"
        append 0 -> state 1
        append 1 -> state 2

    state 2: currently matched "01"
        append 0 -> state 3
        append 1 -> state 0

    state 3: currently matched "010"
        append 0 -> state 4  // "0100" FOUND
        append 1 -> state 2  // "0101", suffix "01"

    state 4:
        "0100" has occurred -> INVALID


    Why state 3 + '1' goes to state 2?

        Current suffix = "010"
        append 1

        "0101"
          ^^
          01

        "01" is still a prefix of "0100"
        so match becomes 2.


    DP STATE
    --------

    rec(level, match)

    level = number of characters already generated
    match = current automaton state

    At every position we have two choices:
        append 0
        append 1
*/


#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;

// dp[level][match]
// match can be 0,1,2,3,4
int dp[100000][5];

int rec(int level, int match) {

    // We have already formed "0100"
    // Therefore this string must NOT be counted.
    if (match == 4) {
        return 0;
    }

    // Generated N characters without finding "0100"
    if (level == n) {
        return 1;
    }

    // Already calculated
    if (dp[level][match] != -1) {
        return dp[level][match];
    }

    int ans = 0;

    /*
        AUTOMATA TRANSITIONS

        match = 0
        current prefix match = ""
            0 -> 1
            1 -> 0
    */
    if (match == 0) {
        ans = rec(level + 1, 1)   // append 0
            + rec(level + 1, 0);  // append 1
    }

    /*
        match = 1
        current prefix match = "0"
            0 -> 1
            1 -> 2
    */
    else if (match == 1) {
        ans = rec(level + 1, 1)   // append 0
            + rec(level + 1, 2);  // append 1
    }

    /*
        match = 2
        current prefix match = "01"
            0 -> 3
            1 -> 0
    */
    else if (match == 2) {
        ans = rec(level + 1, 3)   // append 0
            + rec(level + 1, 0);  // append 1
    }

    /*
        match = 3
        current prefix match = "010"
            0 -> 4  -> "0100" FOUND -> invalid
            1 -> 2  -> suffix "01"
    */
    else if (match == 3) {
        ans = rec(level + 1, 4)   // append 0 -> forbidden
            + rec(level + 1, 2);  // append 1 -> "01"
    }

    return dp[level][match] = ans;
}


signed main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    memset(dp, -1, sizeof(dp));

    cout << rec(0, 0) << '\n';

    return 0;
}
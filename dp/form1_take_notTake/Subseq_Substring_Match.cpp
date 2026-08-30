/*
for infinite take not take
s=0100 has to be there as subsequence
rec(level, x) -> rec(level+1, x=4 means i got the s) or 
if t[x] matches -> rec(level+1, x+1)
if not matches rec(level+1, x)
*/

/*
find the number of N length binary string that doesn't contain "0100"*/
/*s
1. subseq
2. subset
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
string t = "0100";
int dp[100000][5];

int rec(int level, int match) {
    if (match == 4) {
        return 0;
    }

    if (level == n) {
        return 1;
    }

    if (dp[level][match] != -1) {
        return dp[level][match];
    }

    int ans = 0;
    ans += rec(level+1, match+1); // extra char match
    ans += rec(level+1, match); // no match - oppsite put
    return dp[level][match] = ans;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    memset(dp, -1, sizeof(dp));
    cout << rec(0,0);

    return 0;
}




/*
ans += rec(level+1, match+1); // extra char match
    ans += rec(level+1, 0); // no match - oppsite put
for substring this above won't work
let's say 010, u put 1 so macth resets to 0
but last 01 also part of new substring prefix, that's problematix, so 
for substring keep track of last 3 chars, which is not possible incase of subsequence
store last 3 as binary num rather than string
*/



int rec(int level, int match) {
    // 100 -> X, but 0100 -> ☑️, so check len also
    if (match == 4 && level>=4) { // equals to s = "0100"
        return 0;
    }

    if (level == n) {
        return 1;
    }

    if (dp[level][match] != -1) {
        return dp[level][match];
    }

    int ans = 0;
    ans += rec(level+1, ((match<<1)|1)&15); // append 1
    ans += rec(level+1, ((match<<1)|0)&15); // append 0
    return dp[level][match] = ans;
}

int rec(int level, int last3) {

    if (level == n) {
        return 1;
    }

    if (dp[level][last3] != -1) {
        return dp[level][last3];
    }

    int ans = 0;

    // append 1
    ans += rec(level + 1, ((last3 << 1) | 1) & 7);

    // append 0
    // last 3 bits = 010 and adding 0 gives 0100
    if (!(level >= 3 && last3 == 2)) {
        ans += rec(level + 1, (last3 << 1) & 7);
    }

    return dp[level][last3] = ans;
}
/*
using form 1
*/

/*
Longest Increasing Subsequence
--------------------------------

State:

dp(idx, last)

idx  = current position
last = last taken index

Choices:
1. Skip current element
2. Take current element
   only if a[idx] > a[last]

------------------------------------------------
Time Complexity:
O(n^2)
------------------------------------------------
*/

#include<bits/stdc++.h>
using namespace std;

int n;
int a[105];

int dp[105][105];

/*
rec(idx,last) = best answer from here

last = 0 means
no element taken yet

So start:
rec(1,0)

a[0] = -INF
*/
int rec(int idx, int last) {

    // all elements processed
    if(idx == n + 1)
        return 0;

    if(dp[idx][last] != -1)
        return dp[idx][last];

    // option 1 -> skip
    int ans = rec(idx + 1, last);
    // option 2 -> take
    if(a[idx] > a[last]) {
        ans = max(ans, 1 + rec(idx + 1, idx));
    }
    return dp[idx][last] = ans;
}



void print(int idx, int last) {
    if(idx == n + 1) return;

    // if skipping gives optimal
    if(rec(idx, last) == rec(idx + 1, last)) {
        print(idx + 1, last);
    }

    // otherwise take current
    else {
        cout << a[idx] << ' ';
        print(idx + 1, idx);
    }
}



int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for(int i=1;i<=n;i++)
        cin >> a[i];

    // sentinel
    a[0] = -1e9;
    memset(dp, -1, sizeof(dp));

    cout << rec(1,0) << '\n';
    print(1,0);
}


/*Form 2
best ans ending at pos i
dp(level, _) = best ans/ Longest Lis ending at i, starting from 1
2 1 5 3 6 2
dp(level) = max(dp(prev taken) + 1)
like for x[4] = 6, taken dp[4] from prev calculated dp[0],x[0]=2,..dp[3],x[3]=3, where num is smaller*/

int rec(int level) {
    if (level < 0) return 0;
    if (dp[level] != -1) return dp[level];
    int ans = 1;
    for (int i = 0; i < level; ++i) {
        if (x[i] < x[level])
            ans = max(ans, 1 + rec(i));
    }
    return dp[level] = ans;
}
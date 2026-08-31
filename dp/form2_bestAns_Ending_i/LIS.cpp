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

// use (prev value's index) not (prev value), prev val range can be too big
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

int main() {
    for (int i = 0; i < n; ++i) {
        best = max(best, rec(i));
    }
}





/**************** */


#include <bits/stdc++.h>
using namespace std;

int n;
int arr[100005];
pair<int,int> dp[100005]; // {length, count}

pair<int,int> solveRec(int level){
    if(dp[level].first != -1) return dp[level];

    int bestLen = 1;
    int cnt = 1;

    for(int next = level+1; next < n; next++){
        if(arr[next] > arr[level]){
            pair<int,int> res = solveRec(next);
            int len = res.first + 1;

            if(len > bestLen){
                bestLen = len;
                cnt = res.second;          // new best -> reset count
            } else if(len == bestLen){
                cnt += res.second;         // tie -> add count
            }
        }
    }

    // save and return
    return dp[level] = {bestLen, cnt};
}

void solve(){
    cin >> n;
    for(int i = 0; i < n; i++){
        dp[i] = {-1, -1};
        cin >> arr[i];
    }

    pair<int,int> ans = {1, 1};
    for(int i = 0; i < n; i++){
        pair<int,int> res = solveRec(i);
        if(res.first > ans.first){
            ans.first = res.first;
            ans.second = res.second;
        } else if(res.first == ans.first){
            ans.second += res.second;
        }
    }

    cout << ans.first << " " << ans.second << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t = 1;
    // cin >> t;
    while(t--) solve();
}
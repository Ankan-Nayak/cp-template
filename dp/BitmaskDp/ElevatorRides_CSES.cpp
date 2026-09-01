#include <bits/stdc++.h>
using namespace std;
 
// #define int long long
const int inf = 1e9;
 
int n, x;
vector<int> a;
 
pair<int, int> dp[2000000];
int visited[2000000];
 
pair<int, int> rec(int mask) {
    if (mask == 0) return {1,0};
    if (visited[mask] != -1) return dp[mask];
 
    pair<int,int> p = {inf, inf};
    for (int i = 0; i < n; ++i) {
        if ((mask&(1<<i)) == 0) continue;
        int newMask = (mask^(1<<i));
        pair<int,int> temp = rec(newMask);
        int time, space;
        time = temp.first + ((a[i] + temp.second > x) ? 1 : 0);
        space = ((a[i] + temp.second > x) ? a[i] : a[i] + temp.second);
        p = min(p, {time, space});
    }
 
    visited[mask] = true;
    return dp[mask] = p;
}
 
 
signed main() {
    cin >> n >> x;
    a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    memset(visited, -1, sizeof(visited));
    cout << rec((1<<n) - 1).first;
 
    return 0;
}

#include<bits/stdc++.h>
using namespace std;

int arr[1001];
int dp[1001][101];

int n, k;

int rec(int i, int x) {
    if (x < 0) {
        return 1e9;
    }
    if (i == -1) {
        if (x == 0) return 0;
        else return 1e9;
    }

    if (dp[i][x] != -1) return dp[i][x];
    int ans = 1e9;
    // int min_seen = arr[i];
    // for (int j = -1; j <= i - 1; ++j) { // j = -1 means only valid segment from [1,i]
    //     // ans = min(ans, rec(j, x - 1) + min(arr[j + 1...i])); use sparse table
    // }

    // for (int j = i - 1; j >= -1; --j) { 
    //     ans = min(ans, rec(j, x - 1) + min_seen);
    //     min_seen = min(min_seen, arr[j]);
    // }

    int min_seen = 1e9;
    for (int j = i; j >= 0; --j) { 
        min_seen = min(min_seen, arr[j]);
        ans = max(ans, rec(j - 1, x - 1) + min_seen);
    }
    return dp[i][x] = ans;
}
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    memset(dp, -1, sizeof(dp));
    cout << rec(n - 1, k);

    return 0;
}


// subseq, subpartition..use this form


// i have an array, divide the array in k subarray 
// so that total sum of max of their subarray segments is min possible

// 3 5
// [1] [3 2] [5 4] = 1 + 3 + 5 = 9

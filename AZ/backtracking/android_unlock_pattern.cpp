#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

int N;
vector<int> visited(10);
vector<vector<int>> skip(10, vector<int> (10));


int dfs(int curr, int len) {
    if (len == N) return 1;
    int ans = 0;
    visited[curr] = 1;
    for (int nxt = 1; nxt <= 9; ++nxt) {
        if (!visited[nxt]  &&  (!skip[curr][nxt]  ||  visited[skip[curr][nxt]])) {
            visited[nxt] = 1;
            ans += dfs(nxt, len + 1);
            visited[nxt] = 0;
        }
    }
    visited[curr] = 0; // all uncheck after full run
    return ans;
}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);


    // We are numbering
    // 1 2 3
    // 4 5 6
    // 7 8 9

    // These save the connection that skips a point.
    skip[1][3] = skip[3][1] = 2;
    // to join 1 and 3, 2 needs to be pre-selected, or its invalid move.
    skip[1][7] = skip[7][1] = 4;
    skip[3][9] = skip[9][3] = 6;
    skip[7][9] = skip[9][7] = 8;
    skip[1][9] = skip[9][1] = skip[2][8] = skip[8][2] = skip[3][7] = skip[7][3] = skip[4][6] = skip[6][4] = 5;
    // This you will have to create manually.

    cin >> N;
    int ct = 0;
    for (int i = 1; i <= 9; ++i) {
        ct += dfs(i, 1);
    }
    cout << ct;
    
    return 0;
}



// “We can move from curr to nxt if nxt is unused and either there is no skipped cell between them, or the skipped cell has already been visited.”
#include<bits/stdc++.h>
using namespace std;

int n, k;
int ans;

int board[14][14];

int dx[] = {1, 1, 2, 2, -1, -1, -2, -2};
int dy[] = {2, -2, 1, -1, 2, -2, 1, -1};

int bound(int i, int j) {
    return (i >= 0  &&  j >= 0  &&  i < n  &&  j < n);
}

int check(int i, int j) {
    if (board[i][j] == 1) return 0;
    for (int p = 0; p < 8; ++p) {
        int nx = i + dx[p];
        int ny = j + dy[p];
        if (bound(nx, ny)  &&  board[nx][ny]) return 0;
    }
    return 1;
} 

void rec(int idx, int level) { // no of knight placed
    if (level == k) {
        ans++;
        return;
    }
    if (idx >= n * n) return;

    int i = idx / n;
    int j = idx % n;


    if (check(i, j)) {
        // move
        board[i][j] = 1;
        rec(idx + 1, level + 1);
        board[i][j] = 0;
    }
    rec(idx + 1, level);
}

void solve() {
    cin >> n >> k;
    ans = 0;
    rec(0, 0);
    cout << ans << endl; 
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    solve();
    return 0;
}


// // ≈ O(C(n*n, k))
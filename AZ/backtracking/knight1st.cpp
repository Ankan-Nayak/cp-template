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

void rec(int level) { // no of knight placed
    if (level == k) {
        ans += 1;
        return;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (check(i, j)) {
                // move
                board[i][j] = 1;
                rec(level + 1);
                board[i][j] = 0;
            }
        }
    }


}

void solve() {
    cin >> n >> k;
    ans = 0;
    rec(0);
    cout << ans << endl; // includes overcounting
    // cout << ans / k! << endl; as repeating taking
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    solve();
    return 0;
}

// TC -> 0(choice for L1 * choice for L2...choice for Lk) * avg choice
// => N^2 * (N^2-1)....(N^2 - k)) * avg chice = N[for N pos i am doing]
// N^2 C k * N


// 2 3 -> ans = 24 / 3!
#include<bits/stdc++.h>
using namespace std;

int n, cellSize;
int ans;

vector<vector<int>> board(14, vector<int>(14));


bool check(int ch, int row, int col) {
    for (int r = 0; r < n; ++r) {
        if (row != r  &&  board[r][col] == ch) return false;
    }

    for (int c = 0; c < n; ++c) {
        if (col != c  &&  board[row][c] == ch) return false;
    }

    int str = (row / cellSize) * cellSize;
    int stc = (col / cellSize) * cellSize;

    for (int i = str; i < str + cellSize; ++i) {
        for (int j = stc; j < stc + cellSize; ++j) {
            if ((i != row  ||  j != col)  &&  board[i][j] == ch) return false;
        }
    }

    return true;
} 

void rec(int row, int col) { 
    if (col == n) {
        rec(row + 1, 0);
        return;
    }

    if (row == n) {
        ans += 1;
        cout << ans << "th possiblity is : \n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        return;
    }

    if (board[row][col] == 0) {
        for (int i = 1; i <= n; ++i) {
            if (check(i, row, col)) {
                board[row][col] = i;
                rec(row, col + 1);
                board[row][col] = 0;
            }
        }
    }

    else {
        if (check(board[row][col], row, col)) {
            rec(row, col + 1);
        }
    }
}

void solve() {
    cin >> n >> cellSize;
    ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
        }
    }
    rec(0, 0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    solve();
    return 0;
}


// Worst-case TC:  O(n^(n*n)), for every n^2 pos n poss
// Practical TC:   Exponential with heavy pruning
// check():        O(n)
// Space:          O(n^2)

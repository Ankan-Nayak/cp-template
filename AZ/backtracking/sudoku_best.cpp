#include <bits/stdc++.h>
using namespace std;

int n, cellSize;
int ans;
vector<vector<int>> board(14, vector<int>(14));
int takenRow[14];
int takenCol[14];
int takenGrid[14][14];

void makeMove(int ch, int row, int col) {
    board[row][col] = ch;
    takenRow[row] |= (1LL << ch);
    takenCol[col] |= (1LL << ch);
    takenGrid[row / cellSize][col / cellSize] |= (1LL << ch);
}

void revertMove(int ch, int row, int col) {
    board[row][col] = 0;
    takenRow[row] ^= (1LL << ch);
    takenCol[col] ^= (1LL << ch);
    takenGrid[row / cellSize][col / cellSize] ^= (1LL << ch);
}

int getChoices(int row, int col) {
    int taken = takenRow[row] | takenCol[col] | takenGrid[row / cellSize][col / cellSize];
    int notTaken = ((1LL << (n + 1)) - 1) ^ taken;
    if (notTaken & 1) notTaken ^= 1; // remove 0th bit
    return notTaken;
}

void rec(int row, int col) {
    if (col == n) {
        rec(row + 1, 0);
        return;
    }
    if (row == n) {
        ans += 1;
        cout << ans << "th possibility is:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        return;
    }
    
    if (board[row][col] == 0) {
        int chmask = getChoices(row, col);
        for (int i = 1; i <= n; ++i) {
            if (chmask & (1LL << i)) {
                makeMove(i, row, col);
                rec(row, col + 1);
                revertMove(i, row, col);
            }
        }
    } else {
        rec(row, col + 1);
    }
}

void solve() {
    cin >> n >> cellSize;
    ans = 0;
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> board[i][j];
            if (board[i][j] != 0) {  // Critical fix
                makeMove(board[i][j], i, j);
            }
        }
    }
    
    rec(0, 0);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    solve();
    return 0;
}
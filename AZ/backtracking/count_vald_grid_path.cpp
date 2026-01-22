#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<vector<int>> isVisited(7, vector<int>(7, 0));
string s;
int ans = 0;

int isValid(int r, int c) {
    return (r >= 0 && r < 7 && c >= 0 && c < 7);
}

void rec(int row, int col, int len) {
    // Reached destination
    if (row == 6 && col == 0) { // dest
        if (len == 48) ans++; // 48 is string size because start is (0, 0) not given
        return;
    }
    
    // Path too long
    if (len == 48) return;
    
    int r = row, c = col;
    
    // Pruning: Check if we would split the grid
    // Check if left and right are both visited/blocked and up-down are both free
    if ((c == 0 || isVisited[r][c-1]) && (c == 6 || isVisited[r][c+1])) {
        if (r > 0 && r < 6 && !isVisited[r-1][c] && !isVisited[r+1][c]) return;
    }
    
    // Check if up and down are both visited/blocked and left-right are both free
    if ((r == 0 || isVisited[r-1][c]) && (r == 6 || isVisited[r+1][c])) {
        if (c > 0 && c < 6 && !isVisited[r][c-1] && !isVisited[r][c+1]) return;
    }

// #
// ← X →
// #
// border case



//    .
//    ↑
// #  X  #
//    ↓
//    .

//    O   ← you move here
//    ↑
// #  X  #
//    ↓
//    .


// Left is blocked
// Right is blocked
// Up is free
// Down is free
// So X is the only connection between the upper part and the lower part.


// The key problems are:
// No early termination when path splits the grid - If you create a barrier that separates unvisited cells, you can never visit all cells
// Missing boundary collision checks - You should avoid moving along a wall if it creates a forced turn that traps you
    

// 3️⃣ When does the split happen?
// The split happens when the current cell is a bridge
// (also called an articulation point). only one way side possible

// # . . . . 
// # . . # #
// # # x # #
// . # . . #
// . # # # #

// either go upside or downside no coming back to the other par
    char ch = s[len];
    
    // Try Down
    if ((ch == 'D' || ch == '?') && isValid(row + 1, col) && !isVisited[row + 1][col]) {
        isVisited[row + 1][col] = true;
        rec(row + 1, col, len + 1);
        isVisited[row + 1][col] = false;
    }
   
    // Try Up
    if ((ch == 'U' || ch == '?') && isValid(row - 1, col) && !isVisited[row - 1][col]) {
        isVisited[row - 1][col] = true;
        rec(row - 1, col, len + 1);
        isVisited[row - 1][col] = false;
    }
    
    // Try Right
    if ((ch == 'R' || ch == '?') && isValid(row, col + 1) && !isVisited[row][col + 1]) {
        isVisited[row][col + 1] = true;
        rec(row, col + 1, len + 1);
        isVisited[row][col + 1] = false;
    }
    
    // Try Left
    if ((ch == 'L' || ch == '?') && isValid(row, col - 1) && !isVisited[row][col - 1]) {
        isVisited[row][col - 1] = true;
        rec(row, col - 1, len + 1);
        isVisited[row][col - 1] = false;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> s;
    isVisited[0][0] = 1;
    rec(0, 0, 0);
    cout << ans << "\n";
    return 0;
}



// 4^48 ≈ 2.8 × 10^28 paths 😵

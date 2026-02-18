#include<bits/stdc++.h>
using namespace std;

#define int long long
const int inf=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tt;
    cin >> tt;
    while (tt--) {
        int n, m;
        cin >> n >> m;
        
        vector<vector<int>> a(n+1, vector<int>(m+1, 0));  
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                cin >> a[i][j];
            }
        }

        vector<vector<int>> dp(n+2, vector<int>(m+2, inf));  
        dp[n][m] = ((a[n][m] <= 0) ? abs(a[n][m] + 1) : 1);

        cout << dp[n][m] << endl;

        for (int i = n; i >= 1; --i) {
            for (int j = m; j >= 1; --j) {
                if (i == n  &&  j == m) continue;
                int best = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(1LL, best - a[i][j]);    // a[i][j] is -ve, then best + abs(a[i][j])
                                                        // a[i][j] is +ve, then best - abs(a[i][j])
                                                        // min value has to be 1, it can;t be <= 0
            }
        }

        cout << dp[1][1] << '\n';
                

    }
    return 0;
}


// What is dp[i][j]?
// Minimum health Gerald must ENTER cell (i,j) with, to reach exit alive.


/*
Description
Gerald of Rivia also known as The Witcher wants to reach the end of the dungeon. 
The dungeon consists of an n × m grid of rooms laid out in a 2D grid. Gerald is 
initially positioned in the top-left room and must fight his way through to the 
bottom-right room of the dungeon, where the exit is located.

Gerald has an initial health point represented by a positive integer. If at any 
point his health point drops to 0 or below, he dies immediately.

Some of the rooms are guarded by demons (represented by negative integers), so 
Gerald loses health upon entering these rooms; other rooms are either empty 
(represented as 0) or contain magic orbs that increase Gerald's health 
(represented by positive integers).

To reach the exit as quickly as possible, Gerald decides to move only rightward 
or downward in each step.

Return Gerald's minimum initial health so that he can exit the dungeon.

Note that any room can contain threats or power-ups, even the first room Gerald 
enters and the bottom-right room where the exit is located.

Input Format
The first line contains T - the number of test cases.
For each test case:
  - The first line contains two integers n and m.
  - Each of the next n lines contains m integers denoting dungeon[i][j].

Output Format
For each test case, output Gerald's minimum initial health so that he can exit 
the dungeon.

Constraints
1 ≤ T ≤ 100
1 ≤ n ≤ 200
1 ≤ m ≤ 200
−1000 ≤ dungeon[i][j] ≤ 1000

Sample Input
2
3 3
-2 -3 3
-5 -10 1
10 30 -5
1 1
1

Sample Output
7
1

Note
For the first test case, the minimum initial health required is 7 if Gerald 
follows the optimal path: Right -> Right -> Down -> Down.

For the second test case, since the single room has value 1, Gerald needs only 
1 initial health.

*/
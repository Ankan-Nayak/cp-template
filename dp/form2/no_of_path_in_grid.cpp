/*
if 1, that means cell blocked.
I can change at most K blocked to unblocked
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9 + 7;

int n, m, k;
int grid[210][210];
int dp[210][210][410];

int rec(int i, int j, int left)
{

    if (left < 0)
    {
        return 0;
    }

    if (i == n - 1 && j == m - 1)
    {
        if (grid[i][j] == 0 || left > 0)
            return 1;
        return 0;
    }

    if (i == n || j == m)
    {
        return 0;
    }

    if (dp[i][j][left] != -1)
    {
        return dp[i][j][left];
    }

    int ans = 0;
    if (grid[i][j] == 0)
    {
        ans = (rec(i + 1, j, left) % mod + rec(i, j + 1, left) % mod) % mod;
    }
    else
    {
        ans = (rec(i + 1, j, left - 1) % mod + rec(i, j + 1, left - 1) % mod) % mod;
    }

    return dp[i][j][left] = ans % mod;
}

void solve()
{
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> grid[i][j];
        }
    }

    // use this, not memset
    // this loops doesn't give TLE
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            for (int l = 0; l <= k; l++)
            {
                dp[i][j][l] = -1;
            }
        }
    }
    cout << rec(0, 0, k) << endl;
}

signed main()
{
    ios_base::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}

// dp[i][j][k] = number of ways to reach (n,m) from (i,j)
//               using atmax k conversions

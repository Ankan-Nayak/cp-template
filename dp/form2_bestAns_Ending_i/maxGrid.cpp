#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[210][210];
int dp[210][210];

int rec(int i, int j)
{
    if (i == 0 && j == 0)
        return a[0][0];

    if (dp[i][j] != -1)
        return dp[i][j];

    int ans = -1e9;

    if (i > 0)
        ans = max(ans, rec(i - 1, j));

    if (j > 0)
        ans = max(ans, rec(i, j - 1));

    return dp[i][j] = a[i][j] + ans;
}

void printPath(int i, int j)
{
    if (i == 0 && j == 0)
    {
        cout << "(" << i << "," << j << ")";
        return;
    }

    if (i > 0 && dp[i][j] == a[i][j] + rec(i - 1, j))
    {
        printPath(i - 1, j);
    }
    else
    {
        printPath(i, j - 1);
    }

    cout << " -> (" << i << "," << j << ")";
}

void solve()
{
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];

    memset(dp, -1, sizeof(dp));

    cout << "Maximum answer = " << rec(n - 1, m - 1) << '\n';

    cout << "Path = ";
    printPath(n - 1, m - 1);
    cout << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}
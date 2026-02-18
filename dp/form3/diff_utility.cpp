/*
S1 = x m j y a u z
S2 = x m j a a t z

ans = x m j -y a -u +a +t z   (generate this string ans its len)
min length of ans is 9(ans)

can do generate LCS, the take i = 0, j = 0, if both match (), if s1 +, s2 -
*/

// xmjyauz
// xmjaatz


#include<bits/stdc++.h>
using namespace std;

string x, y;
int n, m;

vector<vector<int>> dp;
vector<vector<int>> back;

int rec(int l1, int l2) {
    if (l1 == n && l2 == m) {
        return 0;
    }

    if (dp[l1][l2] != -1) {
        return dp[l1][l2];
    }

    int ans = 1e9;

    if (l1 < n) { // -x[l1]
        if (rec(l1+1, l2) + 1 < ans)
            ans = min(ans, rec(l1+1, l2) + 1);
            back[l1][l2] = 0;
    }

    if (l2 < m) { // +y[l2]
        if (rec(l1, l2+1) + 1 < ans)
            ans = min(ans, rec(l1, l2+1) + 1);
            back[l1][l2] = 1;
    }

    if (l1 < n && l2 < m && x[l1] == y[l2]) { // x[l1]
        if (rec(l1+1, l2+1) + 1 < ans)
            ans = min(ans, rec(l1+1, l2+1) + 1);
            back[l1][l2] = 2;
    }

    return dp[l1][l2] = ans;
}


void generate(int l1, int l2) {
    if (l1 == n && l2 == m) return;
    int ch = back[l1][l2];
    if (ch == 0) {
        cout << "-" << x[l1] << " ";
        generate(l1+1, l2);
    } else if (ch == 1) {
        cout << "+" << y[l2] << " ";
        generate(l1, l2+1);
    } else {
        cout << x[l1] << " ";
        generate(l1+1, l2+1);
    }
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> x >> y;
    n = x.size(), m = y.size();
    dp.assign(n+1, vector<int>(m+1, -1));
    back.assign(n+1, vector<int>(m+1, 0));

    cout << rec(0,0) << '\n';
    generate(0,0);

    return 0;
}

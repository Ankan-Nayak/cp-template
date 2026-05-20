#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001];

string lcs(string& a, string& b) {
    int n = a.size(), m = b.size();
    
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            if (i == 0 || j == 0) { 
                dp[i][j] = 0; 
                continue; 
            }
            
            int ans = max(dp[i-1][j], dp[i][j-1]);
            
            if (a[i-1] == b[j-1])
                ans = max(ans, dp[i-1][j-1] + 1);
            
            dp[i][j] = ans;
        }
    
    // reconstruct
    string result = "";
    int i = n, j = m;

    while (i > 0 && j > 0) {
        if (a[i-1] == b[j-1]) {
            result += a[i-1];
            i--; j--;
        } 
        else if (dp[i-1][j] > dp[i][j-1]) {
            i--;
        } 
        else {
            j--;
        }
    }

    reverse(result.begin(), result.end());
    return result;   // ✅ REQUIRED
}


int main() {
    string a, b;
    cin >> a >> b;
    cout << lcs(a, b) << endl;
}
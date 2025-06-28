void pascalTriangle(int n) {
    for (int i = 0; i < n; i++) {
        int val = 1;
        for (int j = 0; j <= i; j++) {
            cout << val << ' '; 
            val = val * (i - j) / (j + 1); // Compute next binomial coefficient
        }
        cout << endl;
    }
}
// table make i = n, j = r,  => ncr = table[i][j]


#include <bits/stdc++.h>
using namespace std;

#define int long long
const int mod = 1e9;

int nCr[1001][1001]; // n, r <= 1000

void precompute() {
    for(int n = 0; n <= 1000; n++) {
        nCr[n][0] = 1;
        for(int r = 1; r <= n; r++) {
            nCr[n][r] = (nCr[n-1][r-1] + nCr[n-1][r]) % mod;
        }
    }
}

signed main() {
    precompute();
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        for(int r = 0; r <= n; r++) { // fixed boundary to r <= n
            cout << nCr[n][r] << ' ';
        }
        cout << '\n';
    }
    return 0;
}

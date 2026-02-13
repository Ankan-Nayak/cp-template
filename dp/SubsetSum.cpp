// RECURSIVE -> space 0(n * sum)

#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> c;
// dp[index][total sum]
vector<vector<int>> dp;

int f(int pos, int sum) {
    if (sum == 0) return 1;
    if (pos == n) return 0;
    if (dp[pos][sum] != -1) return dp[pos][sum];
    int ans = 0;
    ans = max(ans, f(pos + 1, sum));
    if (c[pos] <= sum) ans = max(ans, f(pos + 1, sum - c[pos]));
    return dp[pos][sum] = ans;
}

signed main() {

    
    cin >> n;
    c.resize(n);
    

    int totalSum = 0;
    for (int j = 0; j < n; ++j) {
        cin >> c[j];
        totalSum += c[j];
    }
    sort(c.begin(), c.end());

    dp.assign(n + 1, vector<int>(totalSum + 1, -1));

    set<int> st;
    for (int i = 1; i <= totalSum; ++i) {
        if (f(0, i)) st.insert(i);
    }

    cout << st.size() << '\n';
    for (auto it : st) {
        cout << it << ' ';
    }
    
    return 0;
}




// ITERATIVE -> space 0(sum)

// #include<bits/stdc++.h>
// using namespace std;
 
// const int inf=1e9;
 
// signed main() {
 
//     int n;
//     cin >> n;
//     vector<int> c(n);
//     for (int j = 0; j < n; ++j) cin >> c[j];
//     sort(c.begin(), c.end());
 
//     vector<int> dp(1e5 + 10, 0);
//     dp[0] = 1;
 
//     for (int j = 0; j < n; ++j) {
//         for (int i = 1e5; i >= 1; --i) {
//             if (c[j] <= i) dp[i] = max(dp[i], dp[i - c[j]]);
//         }
//     }
 
//     set<int> st;
//     for (int i = 1; i <= 1e5; ++i) if (dp[i]) st.insert(i);
 
//     cout << st.size() << '\n';
//     for (auto it : st) cout << it << ' ';
//     return 0;
// }
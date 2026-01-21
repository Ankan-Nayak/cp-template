#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

int N;
vector<char> str;

void rec(int level, int sum) {
    if (sum > 0) return;
    if (level == N  &&  sum != 0) {
        return;
    }
    if (level == N  &&  sum == 0) {
        for (auto it : str) cout << it;
        cout << endl;
        return; 
    }

    str.push_back('(');
    rec(level + 1, sum - 1);

    str.pop_back();

    str.push_back(')');
    rec(level + 1, sum + 1);

    str.pop_back();
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> N;
    rec(0, 0);
    
    return 0;
}


// 4
// (())
// ()()
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

int N, K;
vector<char> str;

void rec(int level, int sum, int mn) {
    if (sum > 0) return;              // invalid prefix
    //if (-sum > N / 2) return;         // too many '('
    //if (-sum > N - level) return;     // cannot close remaining '('
    //if (-mn > K) return;              // depth exceeded
    //if (-mn + (N - level) < K) return;// cannot reach depth K anymore

    if (level == N) {
        if (sum == 0 && mn == -K) {
            for (char c : str) cout << c;
            cout << '\n';
        }
        return;
    }

    // '('
    str.push_back('(');
    rec(level + 1, sum - 1, min(mn, sum - 1));
    str.pop_back();

    // ')'
    str.push_back(')');
    rec(level + 1, sum + 1, mn);
    str.pop_back();
}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> N >> K;
    rec(0, 0, 0);
    
    return 0;
}


// 4
// (())
// ()()
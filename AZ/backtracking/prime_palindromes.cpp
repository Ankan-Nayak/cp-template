#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

int l, r, ans = 0;
string str = "";

int check(int num) {
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return 0;
    }
    return 1;
} 

void rec(int len) {
    if (len > 5) return;

    if (!str.empty()) {
        // even length
        string rev1 = str;
        reverse(rev1.begin(), rev1.end());
        string s1 = str + rev1;
        int x = stoll(s1);
        if (x >= l && x <= r) ans += check(x);

        // odd length
        string rev2 = str;
        rev2.pop_back();
        reverse(rev2.begin(), rev2.end());
        string s2 = str + rev2;
        int y = stoll(s2);
        if (y >= l && y <= r) ans += check(y);
    }

    for (int i = 0; i <= 9; ++i) {
        if (str.empty()  &&  i == 0) continue;
        str += (char)(48 + i);
        rec(len + 1);
        str.pop_back();
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    cin >> l >> r;
    rec(0);
    cout << ans;

    return 0;
}


// in range [0-1e9], 9 length, tc = 9^9
// so only take half of the string
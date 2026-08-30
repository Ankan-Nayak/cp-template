/*
for infinite take not take
s=0100 has to be there as subsequence
rec(level, x) -> rec(level+1, x=4 means i got the s) or 
if t[x] matches -> rec(level+1, x+1)
if not matches rec(level+1, x)
*/

/*
find the number of N length binary string that doesn't contain "0100"*/
/*s
1. subseq
2. subset
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
string t = "0100";

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    return 0;
}
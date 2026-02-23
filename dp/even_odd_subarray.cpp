#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n+1);

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // map[sum parity][len parity]
    // like -2 1 0 -2 -> means -2 to -2 is sum 0

    int cnt[2][2] = {};
    cnt[0][0] = 1;
    int ans = 0;

    int sumParity = 0, lenParity = 0;
    for (int i = 1; i <= n; ++i) {
        sumParity ^= (a[i]&1);
        lenParity = (i&1);

        // I need cnt[1][1];
        ans += cnt[1^sumParity][1^lenParity];
        cnt[sumParity][lenParity]++;
    }
    cout << ans;
    return 0;
}


// len odd -> invalid, valid
// len even -> invalid, valid


// valid subarray len odd(p=1), sum parity odd(p=1)
// 1 1 1 2 2
// 1 1 1 2 2 2 2

// invalid
// 1 1 2 2 -> sum parity = 0, len parity 1 -> +a[i] odd (becomes valid) = odd len, odd sum
// 1 1 1 2 2 2 -> sum parity 1, len parity 0 -> +a[i] even (becomes valid) = odd len, odd sum

// 0(n)














// all subarray with odd sum
class Solution {
public:
    int numOfSubarrays(vector<int>& arr) {
        int md = 1e9+7;
        int ct[2][2] = {};
        ct[0][0] = 1;
        int ans = 0;
        int sumParity = 0;
        for (int i = 0; i < arr.size(); ++i) {
            sumParity ^= (arr[i]&1);
            int lenParity = ((i+1)&1);
            ans += ct[1^sumParity][1^lenParity];
            ans %= md;
            ans += ct[1^sumParity][0^lenParity];
            ans %= md;

            ct[sumParity][lenParity] += 1;
            ct[sumParity][lenParity] %= md;
        }
        return ans;
    }
};


class Solution {
    public int numOfSubarrays(int[] arr) {
        long oddCount=0,prefixSum=0;
        for(int a:arr){
            prefixSum+=a;
            oddCount+=prefixSum%2;
        }
        // only odd sum, all oddsum with ref to even sum
        oddCount+=(arr.length-oddCount)*oddCount;
        return (int)(oddCount%1_000_000_007);
    }
}
// 5️⃣ Meet-in-the-Middle Final Solution
// Logic
// Split array into two halves {1,2,3,4} -> {1,2}, {3,4}
// Generate all subset sums of both halves
// Sort one half
// For each sum in first half:
// Find how many sums in second half satisfy
// a + b ≤ X
// → b ≤ X - a
// → binary search


#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;


// Generates all subset sums of a given array
vector<long long> generate(vector<int>& arr) {
    int n = arr.size();
    vector<long long> sub;

    for (int mask = 0; mask < (1 << n); mask++) {
        long long sum = 0;
        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) {
                sum += arr[j];
            }
        }
        sub.push_back(sum);
    }
    return sub;
}


// N <= 40
// Time: O(2^(N/2) * log(2^(N/2)))
// Space: O(2^(N/2))

long long countSubsets(vector<int>& arr, long long X) {
    int n = arr.size();

    // split array into two halves
    vector<int> left, right;
    for (int i = 0; i < n; i++) {
        if (i < n / 2) left.push_back(arr[i]);
        else right.push_back(arr[i]);
    }

    // generate subset sums
    vector<long long> subL = generate(left);
    vector<long long> subR = generate(right);

    // sort right half sums for binary search
    sort(subR.begin(), subR.end());

    long long ans = 0;

    // for each sum in left, binary search in right
    for (long long s : subL) {
        if (s > X) continue;

        // find how many subR <= X - s
        long long need = X - s;
        ans += upper_bound(subR.begin(), subR.end(), need) - subR.begin();
    }

    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    return 0;
}

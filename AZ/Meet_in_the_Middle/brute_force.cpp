// Given an array arr[] of size N and a value X
// 👉 Count number of subsets whose sum ≤ X

// For every element:
// take it
// don’t take it
// Total subsets = 2^N


// Time: O(2^N)
// Space: O(N) recursion stack
long long cnt = 0;

void brute(int idx, long long sum, vector<int>& arr, long long X) {
    // base case: all elements processed
    if (idx == arr.size()) {
        if (sum <= X) cnt++;
        return;
    }

    // do not take current element
    brute(idx + 1, sum, arr, X);

    // take current element
    brute(idx + 1, sum + arr[idx], arr, X);
}



// Time: O(N * 2^N)
// Space: O(1)
// treat arr[1 0 1 0 0 1], 1 means value taken, 0, means not taken
long long brute_bitmask(vector<int>& arr, long long X) {
    int n = arr.size();
    long long cnt = 0;
    vector<int> subVal; // if need to store val

    for (int mask = 0; mask < (1 << n); mask++) {
        long long sum = 0;

        for (int j = 0; j < n; j++) {
            if (mask & (1 << j)) { // or ((mask>>j) & 1)
                sum += arr[j];
            }
        }
        // sort (remeber this idea)
        if (sum <= X) cnt++;
    }
    return cnt;
}


// ❌ Still the same issue
// N = 20 → 2^20 ≈ 1e6 ✅
// N = 40 → 2^40 ≈ 1e12 ❌
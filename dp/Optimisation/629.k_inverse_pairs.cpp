// put min to max -> 0,1,..n
// f(i,k) = f(i-1,k) + f(i-1,k-1) + f(i-1,k-2)..f(i-1,k-i+1) [Loop cause TLE]
// f(i,k-1) = f(i-1,k-1) + f(i-1,k-2) + f(i-1,k-3)..f(i-1,k-i) [we have calculated this]
// f(i,k) - f(i,k-1) = f(i-1,k) - f(i-1,k-i)
// f(i,k) = f(i,k-1) + f(i-1,k) - f(i-1,k-i)

class Solution {
public:
    int N, K;
    int mod = 1e9+7;
    int dp[1002][1002];
    int rec(int i, int k) {
        if (k < 0) return 0;
        if (k == 0) return 1;
        if (i == 0) 
            return ((k == 0) ? 1 : 0);

        if (dp[i][k] != -1) return dp[i][k];
        int ans = 0;

        ans = (ans + rec(i, k-1)) % mod;
        ans = (ans + rec(i-1, k)) % mod;

        int temp = 0;
        if (k >= i) temp = rec(i-1, k-i);

        ans = (ans + mod - temp) % mod;

        /*
        I am in pos i, from prev which state i can access my ans so that i get dp[i][k] = all poss ans
        */

        
        // whatever permutation is prev..do +1..i, add the min 1 at pos i => ans += (i-1)
        // if put 2 at pos i => ans += (i-1);...
        // brute force from start -> TLE (diff approch rec(0,0))
        // for (int j = 0; j <= i; ++j)
        //     ans = (ans + rec(i+1, k+j)) % mod;
        //     ans %= mod;

        

        return dp[i][k] = ans % mod;
    }
    int kInversePairs(int n, int k) {
        N = n, K = k;
        memset(dp, -1, sizeof(dp));
        int ans = rec(n, k);
        return ans;
    }
};





// PROBLEM
// -------
// f(i,k) = number of permutations of 1..i with exactly k inversions
// Answer = f(n,k) mod 1e9+7


// BASE CASES
// ----------
// f(i,0) = 1        only the sorted permutation has 0 inversions
// f(0,k) = 0        for k > 0, no elements so no inversions possible
// f(i,k) = 0        for k < 0


// STEP 1: BUILD f(i,k) FROM ROW i-1
// ---------------------------------
// Take any permutation of 1..i-1 and insert the largest element i.
// Put i with j elements after it (j = 0 .. i-1).
// Element i is larger than everything, so it forms an inversion
// with each element to its right: exactly j new inversions.

// So a permutation of i-1 elements with (k-j) inversions becomes a
// permutation of i elements with k inversions.

//   f(i,k) = sum over j = 0..i-1 of f(i-1, k-j)

//   f(i,k) = f(i-1,k) + f(i-1,k-1) + ... + f(i-1,k-i+1)        ... (A)

// That is i terms, a window of width i on row i-1.
// Computing this directly costs O(i) per state -> O(n*n*k) total -> TLE.


// STEP 2: WRITE THE SAME FORMULA FOR k-1
// --------------------------------------
// Replace k by k-1 in (A):

//   f(i,k-1) = f(i-1,k-1) + f(i-1,k-2) + ... + f(i-1,k-i)     ... (B)


// STEP 3: COMPARE (A) AND (B)
// ---------------------------
//   (A) = f(i-1,k)  +  [ f(i-1,k-1) + ... + f(i-1,k-i+1) ]
//   (B) =               [ f(i-1,k-1) + ... + f(i-1,k-i+1) ]  +  f(i-1,k-i)

// The bracketed middle part is identical in both.

// Subtract (B) from (A):

//   f(i,k) - f(i,k-1) = f(i-1,k) - f(i-1,k-i)

//   f(i,k) = f(i,k-1) + f(i-1,k) - f(i-1,k-i)                 ... (C)


// STEP 4: WHEN DOES THE SUBTRACTION APPLY
// ---------------------------------------
// The removed term f(i-1,k-i) is a real term only if k-i >= 0.
// If k < i, the window in (A) was clipped at 0 and nothing fell out.

//   if (k >= i):  f(i,k) = f(i,k-1) + f(i-1,k) - f(i-1,k-i)
//   else:         f(i,k) = f(i,k-1) + f(i-1,k)


// FINAL TRANSITION
// ----------------
//   f(i,0) = 1
//   f(0,k) = 0                       (k > 0)
//   f(i,k) = f(i,k-1) + f(i-1,k)     if k < i
//   f(i,k) = f(i,k-1) + f(i-1,k) - f(i-1,k-i)   if k >= i

// Each state is O(1), there are n*k states -> O(n*k) time.


// MODULAR ARITHMETIC
// ------------------
//   ans = (f(i,k-1) + f(i-1,k)) % mod
//   if (k >= i) ans = (ans - f(i-1,k-i) + mod) % mod
//   The "+ mod" prevents a negative value after subtraction.


// CODE (TOP-DOWN)
// ---------------
// int mod = 1e9 + 7;
// int dp[1002][1002];

// int rec(int i, int k) {
//     if (k < 0) return 0;
//     if (k == 0) return 1;
//     if (i == 0) return 0;
//     if (dp[i][k] != -1) return dp[i][k];

//     int ans = 0;
//     ans = (ans + rec(i - 1, k)) % mod;
//     ans = (ans + rec(i, k - 1)) % mod;
//     if (k >= i)
//         ans = (ans - rec(i - 1, k - i) + mod) % mod;

//     return dp[i][k] = ans;
// }


// CODE (BOTTOM-UP, O(k) SPACE)
// ----------------------------
// int kInversePairs(int n, int k) {
//     const int mod = 1e9 + 7;
//     vector<int> prev(k + 1, 0), cur(k + 1, 0);
//     prev[0] = 1;
//     for (int i = 1; i <= n; ++i) {
//         cur[0] = 1;
//         for (int j = 1; j <= k; ++j) {
//             long long v = (long long)cur[j-1] + prev[j];
//             if (j >= i) v -= prev[j-i];
//             v %= mod;
//             if (v < 0) v += mod;
//             cur[j] = (int)v;
//         }
//         swap(prev, cur);
//     }
//     return prev[k];
// }



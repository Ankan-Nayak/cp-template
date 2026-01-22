#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD=1e9+7;

int n, ans = 0;
vector<int> isPrime(100, 0);
vector<int> isTaken(100, 0);
vector<int> val;


/**
 * Backtracking function to find prime cycles
 * @param remaining: number of positions left to fill
 * @param n: total numbers in cycle
 * @param prev: last number placed in the cycle. if cosequetive num sum is prime or not
 * @param parity: 0 = search odd numbers next, 1 = search even numbers next
 */


void rec(int remaining, int parity) {
    if (remaining == 0) {
        // Check if last element forms prime with first (1)
        if (isPrime[1 + val.back()]) ans += 1;
        return;
    }

    for (int i = 2; i <= n; ++i) {
        if (isTaken[i]) continue;
        if (!isPrime[i + val.back()]) continue;
        
        // parity = 0 means need EVEN (i%2 == 0)
        // parity = 1 means need ODD (i%2 == 1)
        if ((i % 2) != parity) continue;  // Skip if wrong parity

        isTaken[i] = 1;
        val.push_back(i);

        rec(remaining - 1, parity ^ 1);  // Flip parity (0↔1)

        val.pop_back();
        isTaken[i] = 0;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // Precompute primes up to 37 (max sum = 18 + 19)
    // 2 = 1 + 1 not possible
    isPrime[2] = isPrime[3] = isPrime[5] = isPrime[7] = isPrime[11] = isPrime[13] = 
    isPrime[17] = isPrime[19] = isPrime[23] = isPrime[29] = isPrime[31] = isPrime[37] = 1;

    cin >> n;

    // Odd N cannot form alternating odd-even cycle
    if (n % 2 == 1) {
        cout << 0 << endl;
        return 0;
    }

    // Fix 1 at start to avoid rotational duplicates
    val.push_back(1);
    isTaken[1] = 1;

    // 1 is odd, so next must be even (parity = 0)
    rec(n - 1, 0);

    cout << ans << endl;
    return 0;
}



// tc for 19 direct too much
// taking oly odd or even when their times
// checking cosequtive num sum is prime or not
// checkng is Taken already or not
// these reduces TLE
#include <bits/stdc++.h>
using namespace std;

/*
VARIANT 1:
----------
Question:
From an array of N numbers Arr, and given a target TARGET,
check if there exist indices a, b, c, d such that:

Arr[a] + Arr[b] + Arr[c] + Arr[d] == TARGET

Constraints:
0 <= a <= b <= c <= d <= N-1
1 <= N <= 1000

Brute Force Idea:
-----------------
Try all possible combinations of (a, b, c, d)
using 4 nested loops.

This guarantees correctness but is very slow.

Why slow?
---------
Total combinations ≈ N^4

If N = 1000:
1000^4 = 10^12 operations ❌ (impossible)

This version is only for understanding and very small N.
*/

bool is4SUMpossible(vector<int>& arr, int n, int target) {

    for (int a = 0; a < n; a++) {
        for (int b = a + 1; b < n; b++) {
            for (int c = b + 1; c < n; c++) {
                for (int d = c + 1; d < n; d++) {

                    if (arr[a] + arr[b] + arr[c] + arr[d] == target) {
                        return true; // quadruple found
                    }

                }
            }
        }
    }

    return false; // no quadruple exists
}




#include <bits/stdc++.h>
using namespace std;

/*
VARIANT 2:
----------
Question:
Does there exist indices a < b < c < d such that:
Arr[a] + Arr[b] + Arr[c] + Arr[d] == TARGET ?

Idea:
-----
Fix (c, d) pairs first and store their sums.
Then for every (a, b), check if:
TARGET - (Arr[a] + Arr[b]) exists as a (c, d) sum.

Order a < b < c < d is maintained by iterating b from right to left
and generating (c, d) after b.
*/

bool is4SUMpossible(vector<int>& arr, int n, int target) {

    unordered_map<int, bool> pos; 
    // pos[sum] = true if some (c,d) exists with that sum

    for (int b = n - 2; b >= 1; b--) {

        // Try all (a, b)
        for (int a = b - 1; a >= 0; a--) {
            int need = target - arr[a] - arr[b];
            if (pos.count(need)) {
                return true; // quadruple exists
            }
        }

        // Now fix c = b and generate all (c, d)
        int c = b;
        for (int d = c + 1; d < n; d++) {
            pos[arr[c] + arr[d]] = true;
        }
    }

    return false;
}





/*
Question:
---------
From an array Arr of size n and a given TARGET,
check whether there exist 4 values (a, b, c, d) such that:

Arr[a] + Arr[b] + Arr[c] + Arr[d] == TARGET

(This version only checks existence, not index ordering)
*/

/*
Idea shown on board:
-------------------
Split 4-SUM into two 2-SUMs

(A + B) + (C + D) = TARGET

Let:
x = A + B
y = C + D

So:
x + y = TARGET
=> y = TARGET - x

Steps:
1) Store all possible (C + D) sums in a map
2) For every (A + B), check if TARGET - (A + B) exists
*/

bool is4SUMpossible(vector<int> arr, int n, int target) {

    // Map to store sums of two elements
    // pos[sum] = 1 means some pair gives this sum
    map<int, int> pos;

    // Step 1: Generate all pair sums (C + D)
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            // Store sum of arr[i] + arr[j]
            pos[arr[i] + arr[j]] = 1;
        }
    }

    // Step 2: Try all pair sums (A + B)
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {

            int need = target - (arr[i] + arr[j]);

            // If complementary sum exists → 4 numbers exist
            if (pos[need]) {
                return true;
            }
        }
    }

    // No valid quadruple found
    return false;
}


// TC -> o(n^2.logn)
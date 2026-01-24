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

    map<int, bool> pos; 
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



// [1, 2, 3, 4, 5]
// fix b = 3 -> right side (all two sum possibilities of c, d)
// left side of b all a
// if such two sum [target - a - b(fixed)] exists means possible





/*
Example:
--------
Array = [1, 2, 3, 4, 5]
Index   =  0  1  2  3  4

Fix b = index 2  (value = 3)


Step 1: Right side of b → generate all (c, d) pairs
---------------------------------------------------
c > b and d > c

Possible (c, d) pairs:
(4,5) → indices (3,4)

Two-sum values on right side:
c + d = 4 + 5 = 9

Store in map:
pos[9] = true


Step 2: Left side of b → try all a
---------------------------------
a < b

Possible a values:
a = 1
a = 2


Step 3: Check condition
-----------------------
We want:
a + b + c + d = TARGET

Rearrange:
c + d = TARGET - a - b


For a = 1:
need = TARGET - 1 - 3 = TARGET - 4
Check if pos[TARGET - 4] exists

For a = 2:
need = TARGET - 2 - 3 = TARGET - 5
Check if pos[TARGET - 5] exists


If ANY of these needed values exists in pos[],
then a < b < c < d is guaranteed
→ 4-SUM is possible


Key Insight:
------------
Fixing b divides the array into:
LEFT  → a
RIGHT → (c, d)

We precompute all right-side two-sums,
then match them with left-side values efficiently.

This reduces 4 nested loops → 2 nested loops.
*/

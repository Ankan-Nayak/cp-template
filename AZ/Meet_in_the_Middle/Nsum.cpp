/*
N-SUM PROBLEM (GENERAL IDEA)
----------------------------

Goal:
-----
Given an array and a TARGET,
check / find / count N elements whose sum = TARGET.


Core Insight (Meet in the Middle):
---------------------------------
Instead of trying all N elements together (O(N^N)),
split the problem into two halves.


If N is EVEN:
-------------
• Split N elements into:
  - Left part  = N / 2 elements
  - Right part = N / 2 elements

• Generate all possible sums of:
  - Left  N/2 elements
  - Right N/2 elements

• Store sums of one side in a map:
  map[sum] = frequency / existence

• For each sum on the other side:
  check if (TARGET - sum) exists in map

• This reduces complexity drastically.


If N is ODD:
------------
• Fix 1 element as the "middle" element

• Remaining elements = N - 1 (which is EVEN)

• Now solve (N - 1)-SUM using meet-in-the-middle:
  - Left  side → (N - 1) / 2 elements
  - Right side → (N - 1) / 2 elements

• For every fixed middle element:
  adjusted_target = TARGET - middle

• Check if left_sum + right_sum = adjusted_target


How 4-SUM fits this idea:
-------------------------
• N = 4 (even)
• Left  = 2 elements  → (a, b)
• Right = 2 elements  → (c, d)

• Store (c + d) in map
• For each (a + b), check:
  TARGET - (a + b)


Why this works:
---------------
• Converts N-SUM → 2-SUM on sums
• Avoids N nested loops
• Time complexity becomes manageable


Interview One-liner:
--------------------
"N-SUM can be optimized using meet-in-the-middle by splitting
the problem into two halves and matching their partial sums."
*/






/*
8-SUM PROBLEM
-------------

N = 8 (even)

Split into:
Left  = 4 elements
Right = 4 elements


Step 1: Generate all possible 4-element sums on LEFT side
----------------------------------------------------------
For all subsets of size 4 taken from left indices:
leftSum = a1 + a2 + a3 + a4
Store in map:
leftMap[leftSum] = frequency


Step 2: Generate all possible 4-element sums on RIGHT side
-----------------------------------------------------------
For all subsets of size 4 taken from right indices:
rightSum = b1 + b2 + b3 + b4


Step 3: Matching
----------------
For each rightSum:
need = TARGET - rightSum

If leftMap[need] exists,
then 8-SUM is possible


Time Complexity:
----------------
Let array size = N

Number of 4-element subsets from N/2 elements:
C(N/2, 4)

Total work ≈ C(N/2,4) + C(N/2,4)
Much smaller than C(N,8)


Key Insight:
------------
Even N-SUM → split equally → match partial sums
(Meet in the Middle)
*/








/*
7-SUM PROBLEM
-------------

N = 7 (odd)

Step 1: Fix one element as middle
---------------------------------
Choose m at index i

Remaining elements = 6 (even)


Step 2: Split remaining 6 elements
----------------------------------
Left  = 3 elements
Right = 3 elements


Step 3: Generate sums
---------------------
Left side:
  all 3-element sums → store in map

Right side:
  all 3-element sums


Step 4: Matching
----------------
For each rightSum:
need = TARGET - m - rightSum

If leftMap[need] exists,
then 7-SUM is possible


Repeat for all choices of middle element m


Why this works:
---------------
Odd N → fix 1 → reduce to even case
*/

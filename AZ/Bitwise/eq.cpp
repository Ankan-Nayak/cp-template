====================== BITWISE CP CHEAT SHEET ======================

1. CORE IDENTITIES
--------------------------------------------------------------------
a + b = (a ^ b) + 2 * (a & b)

a ^ b = a + b - 2 * (a & b)

a & b = (a + b - (a ^ b)) / 2

a ^ b = (a | b) - (a & b)

a | b = (a ^ b) + (a & b)


2. BASIC XOR
--------------------------------------------------------------------
a ^ 0 = a
a ^ a = 0

a ^ b = b ^ a
(a ^ b) ^ c = a ^ (b ^ c)

a ^ b ^ b = a
a ^ b ^ a = b

a ^ b = c  =>  a = b ^ c
a ^ b = c  =>  b = a ^ c

a ^ b ^ c ^ ... ^ x
XOR is unaffected by reordering.


3. BASIC AND
--------------------------------------------------------------------
a & 0 = 0
a & a = a

a & b <= a
a & b <= b

a & (2^k) != 0  => bit k is set


4. BASIC OR
--------------------------------------------------------------------
a | 0 = a
a | a = a

a | b >= a
a | b >= b


5. DE MORGAN'S LAWS
--------------------------------------------------------------------
~(a & b) = (~a) | (~b)
~(a | b) = (~a) & (~b)


6. XOR / AND / OR RELATION
--------------------------------------------------------------------
a ^ b = (a | b) - (a & b)

a | b = (a ^ b) + (a & b)

a + b = (a ^ b) + 2(a & b)


7. SINGLE BIT OPERATIONS
--------------------------------------------------------------------
Check bit k:
    a & (1 << k)

Set bit k:
    a | (1 << k)

Clear bit k:
    a & ~(1 << k)

Toggle bit k:
    a ^ (1 << k)

Get bit k:
    (a >> k) & 1

1 << k = 2^k


8. LOWEST SET BIT
--------------------------------------------------------------------
a & (-a)       = lowest set bit

a & (a - 1)    = removes lowest set bit

a ^ (a & -a)   = removes lowest set bit


9. POWER OF 2
--------------------------------------------------------------------
a > 0 && (a & (a - 1)) == 0

Equivalent:
    a = 2^k


10. SHIFT OPERATIONS
--------------------------------------------------------------------
a << k = a * 2^k

a >> k = floor(a / 2^k)       [for non-negative a]

1 << k = 2^k


11. DIVISION / MULTIPLICATION BY POWERS OF 2
--------------------------------------------------------------------
a * 2       = a << 1
a * 4       = a << 2
a * 8       = a << 3

a / 2       = a >> 1
a / 4       = a >> 2
a / 8       = a >> 3


12. XOR PREFIX: 1 ^ 2 ^ ... ^ n
--------------------------------------------------------------------
n % 4 == 0  => n
n % 4 == 1  => 1
n % 4 == 2  => n + 1
n % 4 == 3  => 0


13. XOR RANGE
--------------------------------------------------------------------
XOR(l ... r) = prefix(r) ^ prefix(l - 1)


14. XOR SWAP
--------------------------------------------------------------------
a ^= b
b ^= a
a ^= b


15. COMPLEMENT
--------------------------------------------------------------------
~a = -a - 1

~~a = a


16. TWO'S COMPLEMENT
--------------------------------------------------------------------
-a = ~a + 1

~a = -a - 1


17. LOWEST SET BIT VALUE
--------------------------------------------------------------------
lowbit(a) = a & (-a)

Example:
a = 1011000
lowbit(a) = 0001000


18. REMOVE LOWEST SET BIT
--------------------------------------------------------------------
a = a & (a - 1)

Example:
1011000
1010111
-------
1010000


19. COUNT SET BITS
--------------------------------------------------------------------
while (a > 0):
    a = a & (a - 1)

Number of iterations = number of set bits.


20. NUMBER OF BITS
--------------------------------------------------------------------
bits(n) = floor(log2(n)) + 1       [n > 0]

Highest set bit position:
floor(log2(n))


21. MAXIMUM VALUE WITH k BITS
--------------------------------------------------------------------
(1 << k) - 1

Example:
k = 4
1111 = 15


22. MASK FOR k BITS
--------------------------------------------------------------------
(1 << k) - 1

First k bits:
a & ((1 << k) - 1)


23. GET LAST k BITS
--------------------------------------------------------------------
a & ((1 << k) - 1)


24. CLEAR LAST k BITS
--------------------------------------------------------------------
a & ~((1 << k) - 1)


25. KEEP BITS FROM k ONWARDS
--------------------------------------------------------------------
a & ~((1 << k) - 1)


26. ISOLATE ALL BUT LOWEST SET BIT
--------------------------------------------------------------------
a & (-a)


27. CLEAR LOWEST SET BIT
--------------------------------------------------------------------
a & (a - 1)


28. CHECK IF EXACTLY ONE BIT IS SET
--------------------------------------------------------------------
a > 0 && (a & (a - 1)) == 0


29. CHECK IF TWO NUMBERS HAVE DIFFERENT BIT k
--------------------------------------------------------------------
((a >> k) & 1) != ((b >> k) & 1)

Equivalent:
((a ^ b) >> k) & 1


30. XOR SWAPS / CANCELLATION
--------------------------------------------------------------------
a ^ b ^ a = b
a ^ b ^ b = a

Every value appearing an even number of times cancels.


31. XOR OF EVEN NUMBER OF SAME VALUES
--------------------------------------------------------------------
a ^ a = 0
a ^ a ^ a ^ a = 0

a appearing even times => contribution = 0


32. XOR OF ODD NUMBER OF SAME VALUES
--------------------------------------------------------------------
a ^ a ^ a = a

a appearing odd times => contribution = a


33. IMPORTANT ORDERING FACT
--------------------------------------------------------------------
For maximum XOR:

Highest differing bit is the deciding bit.

If:
x bit k = 1
y bit k = 0

and all higher bits are equal,

then:
x > y


34. MAX XOR CONDITION
--------------------------------------------------------------------
To maximize a ^ b:

Prefer making the highest possible bit of (a ^ b) = 1.


35. FIXED SUM TRICK
--------------------------------------------------------------------
If a + b = constant:

maximize (a ^ b)
        =
minimize (a & b)

Because:

a ^ b = (a + b) - 2(a & b)


36. FIXED XOR TRICK
--------------------------------------------------------------------
If a ^ b = constant:

a + b = constant + 2(a & b)

So:

minimize (a + b)
        =
minimize (a & b)

maximize (a + b)
        =
maximize (a & b)


37. FIXED OR
--------------------------------------------------------------------
a | b = (a ^ b) + (a & b)

If a | b is fixed:

a ^ b = (a | b) - (a & b)

Therefore:

maximize XOR
    =>
minimize AND


38. FIXED AND
--------------------------------------------------------------------
a + b = (a ^ b) + 2(a & b)

If a & b is fixed:

maximize (a + b)
    =>
maximize (a ^ b)


39. XOR DISTRIBUTION
--------------------------------------------------------------------
a & (b ^ c) = (a & b) ^ (a & c)

a | (b ^ c) != generally (a | b) ^ (a | c)

a ^ (b & c) != generally (a ^ b) & (a ^ c)


40. AND / OR DISTRIBUTION
--------------------------------------------------------------------
a & (b | c) = (a & b) | (a & c)

a | (b & c) = (a | b) & (a | c)


41. ABSOLUTE DIFFERENCE USING XOR
--------------------------------------------------------------------
a ^ b = 0  => a = b

a ^ b != 0 => a != b

Highest set bit of (a ^ b)
= highest position where a and b differ


42. SUBSET / BITMASK CHECK
--------------------------------------------------------------------
(a & b) == a
    =>
all set bits of a are also set in b

Equivalent:
a is a submask of b


43. SUBMASK ENUMERATION
--------------------------------------------------------------------
for (int s = mask; s; s = (s - 1) & mask)

Enumerates every non-zero submask of mask.


44. SUPERSET / MASK CHECK
--------------------------------------------------------------------
(a | b) == b
    =>
a is a submask of b


45. DISJOINT SET BITS
--------------------------------------------------------------------
(a & b) == 0

Means:
a and b have no common set bit.


46. POWER OF TWO RANGE
--------------------------------------------------------------------
Numbers with exactly one set bit:

1, 2, 4, 8, 16, 32, ...


47. ALL ONES
--------------------------------------------------------------------
k bits all set:

(1 << k) - 1

Example:
k = 5

11111 = 31


48. TURN OFF ALL BITS UP TO k
--------------------------------------------------------------------
a & ~((1 << (k + 1)) - 1)


49. GET HIGHEST SET BIT
--------------------------------------------------------------------
highestPowerOf2 <= n

Conceptually:
1 << floor(log2(n))


50. IMPORTANT BITMASK IDENTITY
--------------------------------------------------------------------
x & ~x = 0

x | ~x = all 1s

x ^ ~x = all 1s


51. XOR WITH ALL-ONES MASK
--------------------------------------------------------------------
x ^ ((1 << k) - 1)

=> flips the lowest k bits of x.


52. FLIP LOWEST k BITS
--------------------------------------------------------------------
x ^= (1 << k) - 1


53. KEEP LOWEST k BITS
--------------------------------------------------------------------
x &= (1 << k) - 1


54. REMOVE LOWEST k BITS
--------------------------------------------------------------------
x &= ~((1 << k) - 1)


55. RANGE BITMASK
--------------------------------------------------------------------
Bits [l ... r]:

((1 << (r - l + 1)) - 1) << l


56. SET RANGE [l ... r]
--------------------------------------------------------------------
x |= ((1 << (r - l + 1)) - 1) << l


57. CLEAR RANGE [l ... r]
--------------------------------------------------------------------
x &= ~(((1 << (r - l + 1)) - 1) << l)


58. XOR RANGE [l ... r]
--------------------------------------------------------------------
x ^= ((1 << (r - l + 1)) - 1) << l


59. UNIQUE NUMBER
--------------------------------------------------------------------
If every number appears twice except one:

ans = a1 ^ a2 ^ ... ^ an

All pairs cancel.


60. TWO UNIQUE NUMBERS
--------------------------------------------------------------------
If every number appears twice except x and y:

all = a1 ^ a2 ^ ... ^ an

all = x ^ y

lowbit = all & (-all)

Use lowbit to divide numbers into two groups.

XOR each group separately:
=> x and y


61. XOR MAXIMIZATION GREEDY
--------------------------------------------------------------------
When maximizing XOR:

Start from highest bit.
Try to make XOR bit = 1.
If possible, choose that option.

Higher bit > all lower bits combined.


62. XOR OF CONSECUTIVE NUMBERS
--------------------------------------------------------------------
l ^ (l+1) ^ ... ^ r
= prefix(r) ^ prefix(l-1)


63. IMPORTANT RANGE FACT
--------------------------------------------------------------------
XOR of a number with itself = 0.

Therefore:
XOR of every number in a range appearing twice = 0.


64. BIT PARITY
--------------------------------------------------------------------
(a >> k) & 1

Returns:
1 => kth bit is set
0 => kth bit is not set


65. COMMON CP TRANSFORMATION
--------------------------------------------------------------------
a - b
= (a ^ b) - 2 * (a & ~b)

a + b
= (a ^ b) + 2 * (a & b)


66. BITWISE SUBTRACTION RELATION
--------------------------------------------------------------------
a - b
= a + (~b + 1)

Useful when thinking about binary subtraction / two's complement.


67. IMPORTANT INEQUALITY
--------------------------------------------------------------------
a ^ b <= a | b

a & b <= a ^ b      NOT always true
a & b <= a | b      ALWAYS true


68. ABSOLUTE DIFFERENCE
--------------------------------------------------------------------
|a - b| is NOT generally equal to a ^ b.

But:
a ^ b = a + b - 2(a & b)

So XOR measures bit differences, not numerical distance.


69. BINARY TRIE MAX XOR IDEA
--------------------------------------------------------------------
For each bit from HIGH -> LOW:

Prefer opposite bit.

If x has:
bit = 0 -> search for 1
bit = 1 -> search for 0

This maximizes x ^ y.


70. THE MOST IMPORTANT ONES TO MEMORIZE
--------------------------------------------------------------------
a + b = (a ^ b) + 2(a & b)

a ^ b = a + b - 2(a & b)

a ^ b = (a | b) - (a & b)

a & (a - 1) = remove lowest set bit

a & (-a) = lowest set bit

a is power of 2:
a > 0 && (a & (a - 1)) == 0

1 << k = 2^k

(a >> k) & 1 = kth bit

(1 << k) - 1 = k ones

XOR prefix:
n%4==0 -> n
n%4==1 -> 1
n%4==2 -> n+1
n%4==3 -> 0

FIXED SUM:
maximize XOR <=> minimize AND

SUBMASK:
(a & b) == a

DISJOINT:
(a & b) == 0

MAX XOR:
maximize highest differing bit first.
====================================================================
// 1. Add two numbers without +
// a + b
int add(int a, int b) {
    while (b != 0) {
        int carry = a & b;
        a = a ^ b;
        b = carry << 1;
    }
    return a;
}

Logic
- a ^ b → adds bits without carry
- a & b → finds where carry is generated
- carry << 1 → moves the carry to the next bit
- Repeat until there is no carry.
Example:
a = 5  = 0101
b = 3  = 0011

a ^ b = 0110  → 6
a & b = 0001  → carry
carry << 1 = 0010

0110 ^ 0010 = 0100 → 4
0110 & 0010 = 0010 → carry
0010 << 1 = 0100

0100 ^ 0100 = 0000
0100 & 0100 = 0100
0100 << 1 = 1000
...


// 2. Swap two numbers without a temporary variable
a = a ^ b;
b = a ^ b;
a = a ^ b;

// 3. Check even/odd without %
if (n & 1)
    cout << "Odd";
else
    cout << "Even";

// 4. Multiply by 2 without *
n = n << 1;

// 5. Divide by 2 without /
n = n >> 1;

// 6. Check if number is power of 2
bool isPowerOfTwo = (n > 0) && ((n & (n - 1)) == 0);

// 7. Find unique element when every other element appears twice
int ans = 0;
for (int x : nums)
    ans ^= x;

// 8. Find missing number from 0 to n
int ans = n;
for (int i = 0; i < n; i++)
    ans ^= i ^ nums[i];

// 9. Check if two numbers have opposite signs
bool oppositeSigns = (a ^ b) < 0;

// 10. Clear the lowest set bit
n = n & (n - 1);


// Any lowest bit number is x =101100100
// Then x-1 would be
// =101100R11
// Every bit after lowest bit would be set except that bit 
// Like n&n-1

// 11. Get the lowest set bit
int lowestBit = n & (-n);

// 12. Count set bits
int count = 0;
while (n) {
    n = n & (n - 1);
    count++;
}

// 13. Set the i-th bit
n = n | (1 << i);

// 14. Clear the i-th bit
n = n & ~(1 << i);

// 15. Toggle the i-th bit
n = n ^ (1 << i);

// 16. Check if the i-th bit is set
bool set = n & (1 << i);

// 17. Find maximum of two numbers without if
int mx = a ^ ((a ^ b) & -(a < b));

// 18. Find minimum of two numbers without if
int mn = b ^ ((a ^ b) & -(a < b));

// 19. Negate a number without -
int neg = ~n + 1;

// 20. Check if two numbers are equal without ==
bool equal = !(a ^ b);

// 21. Multiply by 4 without *
n = n << 2;

// 22. Divide by 4 without /
n = n >> 2;



// store pos of bits in vector of vector 30 length
// for every number 30 cols to store bit set/ unset



// for every pos unset >= set always from 0
// ..0.. or ..1.. as 0 comes 1st always
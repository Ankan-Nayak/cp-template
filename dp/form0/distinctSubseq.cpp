void SOLVE() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    
    // dp[i] = number of distinct subsequences ending at position i
    // prefix[i] = total distinct subsequences in s[0...i-1]
    vector<long long> dp(n + 1, 0);
    vector<long long> prefix(n + 1, 0);
    
    // last[c] = last position where character c appeared (1-indexed)
    vector<int> last(26, 0);
    
    // Base case: empty subsequence
    dp[0] = 1;
    prefix[0] = 1;
    
    for (int i = 1; i <= n; i++) {
        char ch = s[i - 1];  // Current character (0-indexed in original string)
        int charIndex = ch - 'a';
        
        // Initially, we can append current character to all previous subsequences
        dp[i] = prefix[i - 1];
        
        // Remove duplicates: if this character appeared before
        if (last[charIndex] > 0) {
            int prevPos = last[charIndex];
            // Subtract subsequences that would create duplicates
            dp[i] -= prefix[prevPos - 1];
        }
        
        // Update prefix sum
        prefix[i] = dp[i] + prefix[i - 1];
        
        // Update last occurrence of current character
        last[charIndex] = i;
    }
    
    // Output total distinct subsequences (excluding empty subsequence)
    cout << prefix[n] - 1 << '\n';
}







/*
EXAMPLE: Counting DISTINCT Subsequences using DP + Last Occurrence Trick

Let the string be:

s = "aba"
n = 3

Definitions:

prefix[i] = total distinct subsequences using first i characters (including empty)
dp[i]     = new subsequences formed at position i

Base Case:

prefix[0] = 1   → { "" }  (empty subsequence)

We process characters one by one.

------------------------------------------------------------
STEP-BY-STEP TABLE

i | s[i] | dp[i] calculation                          | prefix[i]
------------------------------------------------------------

0 |  -   | base case                                  | 1
          subsequences: { "" }

------------------------------------------------------------

1 |  a    | dp[1] = prefix[0] = 1                     | 
*/









/*
PROBLEM: Count Distinct Subsequences of a String

Given a string s of length n consisting of lowercase English letters,
determine how many DISTINCT subsequences can be formed.

A subsequence is formed by deleting zero or more characters without
changing the relative order of remaining characters.

Two subsequences are considered different if their resulting strings differ.

The EMPTY subsequence is NOT counted in the final answer.

------------------------------------------------------------

CORE IDEA

When processing characters one by one:

At position i:

Every existing subsequence can either:

1) Ignore s[i]
2) Append s[i]

So naive recurrence:

total[i] = 2 * total[i-1]

BUT duplicates arise when the same character appeared earlier.

We must subtract subsequences counted previously.

------------------------------------------------------------

DP DEFINITIONS

Let:

prefix[i] = number of distinct subsequences using first i characters
dp[i]     = number of NEW subsequences created at position i

Base:

prefix[0] = 1   // only empty subsequence

------------------------------------------------------------

TRANSITION

For character s[i]:

We can append s[i] to ALL previous subsequences:

dp[i] = prefix[i-1]

If s[i] appeared before at position prevPos:

Some subsequences were already formed when that previous occurrence
was processed.

Those duplicates = prefix[prevPos - 1]

So:

dp[i] -= prefix[prevPos - 1]

Then update:

prefix[i] = prefix[i-1] + dp[i]

------------------------------------------------------------

WHY SUBTRACTION WORKS

Suppose character 'a' appears again.

All subsequences ending before its previous occurrence already
generated subsequences using 'a'.

Appending again would duplicate them.

Hence remove prefix[prevPos - 1].

------------------------------------------------------------

FINAL ANSWER

Exclude empty subsequence:

answer = prefix[n] - 1

------------------------------------------------------------

IMPLEMENTATION LOGIC

Track last occurrence of each character.

last[c] = most recent position of character c (1-indexed)

------------------------------------------------------------

CODE

for i = 1 to n:

    charIndex = s[i-1] - 'a'

    dp[i] = prefix[i-1]

    if last[charIndex] exists:
         dp[i] -= prefix[last[charIndex] - 1]

    prefix[i] = prefix[i-1] + dp[i]

    update last[charIndex] = i

------------------------------------------------------------

COMPLEXITY

Time  : O(n)
Space : O(n)

------------------------------------------------------------

KEY INSIGHT

Distinct subsequences grow exponentially,
but duplicates are removed using last occurrence trick.
*/
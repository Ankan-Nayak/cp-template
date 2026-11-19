
/*
Problem: Minimum Changes to Make K Semi-Palindromes

Given a string s and integer k, partition s into exactly k
non-empty substrings such that every substring becomes a
semi-palindrome with minimum total character changes.

Semi-Palindrome:
1. Choose a divisor d of substring length.
2. 1 <= d < len.
3. Divide characters into d groups:
   Group x = s[x], s[x+d], s[x+2*d], ...
4. Every group must be a palindrome.

Logic:

1. Precompute minAns[l][r]:
   Minimum changes required to make s[l...r] a semi-palindrome.
   Try every valid divisor d and count mismatched pairs
   in each group.

2. foundCount(l, r, d):
   Compare characters from both ends of each group.
   Each mismatched pair requires one change.

3. DP:
   dp[i][k] = minimum changes to partition suffix
   starting at i into exactly k more substrings.

   Transition:
   dp[i][k] = min(
       minAns[i][j] + dp[j+1][k+1]
   )

4. Base cases:
   i == n:
       return 0 if k == K, otherwise INF.

   k > K:
       return INF.

5. Every substring must have length >= 2
   because a length-1 substring has no valid divisor.

Complexity:
Precomputation: O(n^3 * sqrt(n)) upper bound
DP: O(n^2 * K)
Space: O(n^2)
*/



class Solution {
public:
    int n;
    int K;
    string str;
    int dp[201][201];
    int minAns[201][201];


    int foundCount(int l, int r, int d) {
        int totalChange = 0;

        for (int start = 0; start < d; ++start) {
            int left = l + start;
            int right = left + ((r - left) / d) * d;

            while (left < right) {
                if (str[left] != str[right]) {
                    totalChange++;
                }
                left += d;
                right -= d;
            }
        }

        return totalChange;
    }

    int check(int l, int r) {
        int len = r - l + 1, minChange = 1e9;
        for (int d = 1; d * d <= len; ++d) {
            if (len % d == 0) {
                minChange = min(minChange, foundCount(l, r, d));

                int other_div = len / d;
                if (d != 1) minChange = min(minChange, foundCount(l, r, other_div));
            }
        }
       
        return minChange;
    }

    int rec(int i, int k) {
        if (i == n) {
            return (k == K) ? 0 : 1e9;
        }
        if (k > K) return 1e9;
        if (dp[i][k] != -1) return dp[i][k];
        int ans = 1e9;
        for (int j = i + 1; j < n; ++j) {
            ans = min(ans, minAns[i][j] + rec(j + 1, k + 1));
        }
        return dp[i][k] = ans;
    }

    int minimumChanges(string s, int k) {
        n = s.size();
        K = k;
        str = s;
    
        for (int l = 0; l < n; ++l) {
            for (int r = l; r < n; ++r) {
                minAns[l][r] = 1e9;
                minAns[l][r] = min(minAns[l][r], check(l, r));
            }
        }


        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                cout << i << ' ' << j << " -> " << minAns[i][j] << endl;
            }
            cout << endl;
        }

        memset(dp, -1, sizeof(dp));
        return rec(0,0);
    }
};



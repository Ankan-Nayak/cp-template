class Solution {
public:
    vector<int> a;
    double total = 0, avg = 0;
    int n;
    map<tuple<int,int,int>, bool> dp;
    int rec (int i, int cur, int cnt) {
        if (i >= n) 
            return (cnt > 0 && cnt < n && (cnt * total) == (cur * n));

        tuple<int, int, int> key = {i, cur, cnt};
        if (dp.count(key)) 
            return dp[key];

        int ans = 0;

        ans |= rec(i+1, cur, cnt);
        ans |= rec(i+1, cur+a[i], cnt+1);
        return dp[key] = ans;
    }
    bool splitArraySameAverage(vector<int>& nums) {
        n = nums.size();
        a = nums;
        for (auto it : nums) total += it;
        avg = total / n;      

        int ans = rec(0, 0, 0);

        cout << avg;
        return ans;
    }
};

// TLE



class Solution {
public:
    int n, total;
    vector<int> a;

    map<tuple<int,int,int>, bool> dp;

    // Can we choose exactly cnt elements from [i...n-1]
    // whose sum is rem?
    bool rec(int i, int cnt, int rem) {

        if (cnt == 0)
            return rem == 0;

        if (i == n)
            return false;

        if (n - i < cnt)
            return false;

        if (rem < 0)
            return false;

        auto key = make_tuple(i, cnt, rem);

        if (dp.count(key))
            return dp[key];

        bool ans = false;

        // Don't take
        ans |= rec(i + 1, cnt, rem);

        // Take
        ans |= rec(i + 1, cnt - 1, rem - a[i]);

        return dp[key] = ans;
    }

    bool splitArraySameAverage(vector<int>& nums) {

        a = nums;
        n = nums.size();

        total = 0;
        for (int x : nums)
            total += x;

        // Only need to check subset sizes up to n/2
        for (int cnt = 1; cnt <= n / 2; cnt++) {

            // Required sum must be an integer
            if ((total * cnt) % n != 0) 
                continue;

            int target = (total * cnt) / n;

            // dp.clear();

            if (rec(0, cnt, target))
                return true;
        }

        return false;
    }
};


// TLE




// string key use
class Solution {
public:
    int n, total;
    vector<int> a;

    unordered_map<string, bool> dp;

    bool rec(int i, int cnt, int rem) {

        if (cnt == 0)
            return rem == 0;

        if (i == n)
            return false;

        string key = to_string(i) + "#" +
                     to_string(cnt) + "#" +
                     to_string(rem);

        if (dp.count(key))
            return dp[key];

        if (a[i] <= rem) {
            return dp[key] =
                rec(i + 1, cnt - 1, rem - a[i]) ||
                rec(i + 1, cnt, rem);
        }

        return dp[key] =
            rec(i + 1, cnt, rem);
    }

    bool splitArraySameAverage(vector<int>& nums) {

        a = nums;
        n = nums.size();

        total = 0;
        for (int x : nums)
            total += x;

        for (int cnt = 1; cnt <= n / 2; cnt++) {

            if ((total * cnt) % n != 0)
                continue;

            int target = (total * cnt) / n;

            if (rec(0, cnt, target))
                return true;
        }

        return false;
    }
};




Think of it as 0/1 Subset Sum + count.

State:
    dp[cnt][sum] = can we choose exactly `cnt` elements
                    with total sum `sum`?

Initially:
    dp[0][0] = true

For every number x:
    for cnt from n/2 down to 1:
        for every sum possible in dp[cnt-1]:

            newSum = sum + x

            dp[cnt][newSum] = true

            Check:
                newSum / cnt == total / n
            =>  newSum * n == total * cnt

Why cnt goes backwards?
    Because each x can be used only ONCE.
    Going backwards prevents the current x from being
    used again in the same iteration.

Example:
    nums = [1, 2, 3]

    Initially:
        dp[0] = {0}

    Process x = 1:
        dp[1] = {1}

    Process x = 2:
        From dp[0] = {0}:
            dp[1] gets 2

        From dp[1] = {1}:
            dp[2] gets 3

    So:
        dp[1] = {1, 2}
        dp[2] = {3}

The `i` state from recursion disappears because
the outer loop itself represents which elements
have been processed:

    recursive:  dp[i][cnt][sum]
    iterative: dp[cnt][sum]
                ↑
             i handled by for(x : nums)


class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size();

        int total = accumulate(nums.begin(), nums.end(), 0);

        // dp[cnt] = all possible sums using exactly cnt elements
        vector<unordered_set<int>> dp(n / 2 + 1);

        dp[0].insert(0);

        for (int x : nums) {

            // Go backwards so x is used only once
            for (int cnt = n / 2; cnt >= 1; cnt--) {

                for (int sum : dp[cnt - 1]) {

                    int newSum = sum + x;

                    if (newSum * n == total * cnt)
                        return true;

                    dp[cnt].insert(newSum);
                }
            }
        }

        return false;
    }
};
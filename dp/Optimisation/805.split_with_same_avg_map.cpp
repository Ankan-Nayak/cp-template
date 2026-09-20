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
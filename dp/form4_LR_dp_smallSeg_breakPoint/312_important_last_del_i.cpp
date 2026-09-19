312. Burst Balloons


You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.

If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.

Return the maximum coins you can collect by bursting the balloons wisely.




class Solution {
public:
    int n;
    int dp[310][310];
    vector<int> a;
    int rec(int l, int r) {
        if (l > r) return 0;
        if (dp[l][r] != -1) return dp[l][r];
        int ans = 0;
        for (int i = l; i <= r; ++i) {
            int left = rec(l,i-1);
            int right = rec(i+1,r);
            // mark this line
            // i is the last delete in [l,r]
            // so outside range is l-1, r+1
            int cost = a[l-1] * a[i] * a[r+1];
            ans = max(ans, left + right + cost);
        }
        return dp[l][r] = ans;
    }
    int maxCoins(vector<int>& nums) {
        n = nums.size();
        a.push_back(1);
        for (auto it : nums) a.push_back(it);
        a.push_back(1);
        memset(dp, -1, sizeof(dp));
        int ans = rec(1, n);
        return ans;
    }
};

/*
LR dp
*/
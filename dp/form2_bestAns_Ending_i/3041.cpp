class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        map<int, int> dp;
        sort(nums.begin(), nums.end());

        // max ans ending at i
        int ans = 0;
        for (int i = 0; i < nums.size(); ++i) {
            dp[nums[i] + 1] = dp[nums[i]] + 1; // extend 1 bit
            dp[nums[i]] = dp[nums[i] - 1] + 1;
            ans = max({ans, dp[nums[i]], dp[nums[i] + 1]});
        }
        return ans;
    }
};
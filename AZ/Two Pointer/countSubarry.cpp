class Solution {
public:
// for each i, find lowestR - lowestL + 1, add it to ans
    long long countSubarrays(vector<int>& nums, int k, int m) {
        map<int, int> mpL, mpR;
        long long ans = 0;
        int goodL = 0, goodR = 0, n = nums.size();
        int lowestL = 0, lowestR = 0;
        for (int i = 0; i < n; ++i) {
            mpL[nums[i]]++;
            if (mpL[nums[i]] == m) goodL += 1;
            mpR[nums[i]]++;
            if (mpR[nums[i]] == m) goodR += 1;

            while (mpR.size() > k) {
                mpR[nums[lowestR]] -= 1;
                if (mpR[nums[lowestR]] == m-1) goodR -= 1;
                if (mpR[nums[lowestR]] == 0) mpR.erase(nums[lowestR]);
                lowestR += 1;
            }
            while (lowestL < lowestR && mpL.size() > k) {
                mpL[nums[lowestL]] -= 1;
                if (mpL[nums[lowestL]] == m-1) goodL -= 1;
                if (mpL[nums[lowestL]] == 0) mpL.erase(nums[lowestL]);
                lowestL += 1;
            }
            while (lowestR < n && mpR.size() == k && mpR[nums[lowestR]] > m) {
                mpR[nums[lowestR]] -= 1;
                if (mpR[nums[lowestR]] == 0) mpR.erase(nums[lowestR]);
                lowestR += 1;
            }

            if (mpR.size() == k && goodL == k && goodR == k) {
                ans += (lowestR - lowestL + 1);
            }
        }
        return ans;
    }
};

// count no of subarray with k unq, and each unq has atleast m freq
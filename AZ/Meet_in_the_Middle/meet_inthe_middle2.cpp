/*
Q3. Minimum Removals to Achieve Target XOR©leetcode
*/

class Solution {
public:
    vector<pair<int, int>> generateSubset(vector<int> &a) {
        int n = a.size();
        vector<pair<int,int>> id;
        for (int mask = 0; mask < (1 << n); ++mask) {
            int sum = 0;
            for (int b = 0; b < n; ++b) {
                if (mask & (1 << b)) sum ^= a[b];
            }
            id.push_back({sum, n-__builtin_popcount(mask)});
        }
        return id;
    }
    int minRemovals(vector<int>& nums, int target) {
        int n = nums.size();
        vector<int> left, right;
        for (int i = 0; i < n; ++i) {
            if (i < n/2) left.push_back(nums[i]);
            else right.push_back(nums[i]);
        }

        vector<pair<int,int>> gL = generateSubset(left);
        vector<pair<int,int>> gR = generateSubset(right);

        // sort(gR.begin(), gR.end());
        map<int, int> mp;
        for (auto &it : gR) {
            if (mp.find(it.first) != mp.end()) {
                mp[it.first] = min(it.second, mp[it.first]);
            } else {
                mp[it.first] += it.second;
            }
        }

        int ans = INT_MAX;
        for (int i = 0; i < gL.size(); ++i) {
            int rest = (target ^ gL[i].first);
            if (mp.find(rest) != mp.end()) {
                ans = min(ans, gL[i].second + mp[rest]);
            }
        }
        if (ans == INT_MAX) {
            ans = -1;
        }
        return ans;
    }
};
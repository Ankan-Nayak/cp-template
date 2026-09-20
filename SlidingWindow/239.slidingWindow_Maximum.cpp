/*
k size window want max
sparse table 
multiset

*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> ans;
        multiset<int> mst;
        for (int i = 0; i < k; ++i) {
            mst.insert(nums[i]);
        }
        ans.push_back(*mst.rbegin());
        for (int i = k; i < nums.size(); ++i) {
            mst.erase(mst.find(nums[i - k]));
            mst.insert(nums[i]);
            ans.push_back(*mst.rbegin());
        }
        return ans;
    }
};

// importatnt to understand
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        deque<int> dq; // store pos
        vector<int> ans; // store max nums[i] for k window
        for (int i = 0; i < n; ++i) {
            while (!dq.empty() && nums[i] >= nums[dq.back()]) {
                dq.pop_back();
            }
            dq.push_back(i);
            while (dq.front() <= i - k) {
                dq.pop_front();
            }
            if (i >= k-1) {
                ans.push_back(nums[dq.front()]);
            }
        }
        return ans;
    }
};
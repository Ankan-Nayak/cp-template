class Solution {
public:
    int trap(vector<int>& height) {
        int n = height.size() - 1;
        int left = 1, right = n - 1;
        int max_left_h = height[0], max_right_h = height[n];
        int ans = 0;
        while (left <= right) {
            if (max_left_h >= max_right_h) {
                ans += max(0, max_right_h - height[right]);
                max_right_h = max(max_right_h, height[right]);
                right -= 1;
            } else {
                ans += max(0, max_left_h - height[left]);
                max_left_h = max(max_left_h, height[left]);
                left += 1;
            }
        }
        return ans;
    }
};
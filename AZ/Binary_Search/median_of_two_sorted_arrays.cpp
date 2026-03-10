class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();
        if (n < m) {
            swap(nums1, nums2);
            swap(n, m);
        }
        
        int p = p = (n + m + 1) / 2;
        int low = 0, high = p;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int r1 = INT_MAX, r2 = INT_MAX;
            int l1 = INT_MIN, l2 = INT_MIN;
            int rest = p - mid;
            if (mid < n) r1 = nums1[mid];
            if (rest < m) r2 = nums2[rest];
            if (mid - 1 >= 0) l1 = nums1[mid - 1];
            if (rest - 1 >= 0) l2 = nums2[rest - 1];
            

            if (r1 >= l2 && r2 >= l1) {
                if ((n + m) % 2 == 1) return max(l1, l2);
                else return ((double)(max(l1, l2) + min(r1, r2))) / 2.0;
            }
            else if (l1 >= r2) {
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return -1;
    }
};
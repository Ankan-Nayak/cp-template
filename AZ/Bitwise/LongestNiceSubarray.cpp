class Solution {
public:
    int longestNiceSubarray(vector<int>& nums) {
        int n = nums.size();
        int len = 1;
        int i = 0, j = 0, usedBit = 0;
        while (i < n) {
            if ((usedBit & nums[i]) == 0) {
                usedBit |= nums[i];
                len = max(len, i - j + 1);
                i += 1;
            } else {
                usedBit ^= nums[j];
                j += 1;
            }
        }
        return len;
    }
};

/* 
what's the maximum possible sum of the subarray -> 30 bits max -> so 30
if ans is 20, then i can take 2^20 poss and check

if decided to take value x where bit set at position p
then for all others taken in answer has to be unset at pos p

if any pair in ans & is 0 then all ands also give zero -> x&x&..xn = 0
BS on length gives ans tho but how check func ?
dp on bits ?
*/
class Solution {
public:
    int n;
    vector<int> a;
    int dp[1010];
    int rec(int i) {
        if (i >= n-1) return 0;
        if(dp[i] != -1) {
            return dp[i];
        }
        int ans = 0;
        ans = max(ans, a[i] + rec(i+2));
        ans = max(ans, rec(i+1));

        return dp[i] = ans;
    }

    int rec2(int i) {
        if (i >= n) return 0;
        if(dp[i] != -1) {
            return dp[i];
        }
        int ans = 0;
        ans = max(ans, a[i] + rec2(i+2));
        ans = max(ans, rec2(i+1));

        return dp[i] = ans;
    }
    int rob(vector<int>& nums) {
        n = nums.size();
        a = nums;
        memset(dp,-1,sizeof(dp));
        int res1 = rec(0);
        memset(dp,-1,sizeof(dp));
        int res2 = rec2(1);
        
        if (n == 1) res2 = nums[0];
        return max(res1, res2);
    }
};




class Solution {
public:
    int n;
    vector<int> a;
    int dp[1010][2];
    int rec(int i, int end) {
        if (n == 1) return a[0];
        int e = ((end == 0) ? n-1 : n);
        if (i >= e) return 0;
        if(dp[i][end] != -1) {
            return dp[i][end];
        }
        int ans = 0;
        ans = max(ans, a[i] + rec(i+2, end));
        ans = max(ans, rec(i+1, end));

        return dp[i][end] = ans;
    }

    int rob(vector<int>& nums) {
        n = nums.size();
        a = nums;
        memset(dp,-1,sizeof(dp));
        int res1 = rec(0, 0);
        int res2 = rec(1, 1);
        
        return max(res1, res2);
    }
};





class Solution {
public:
    int n;
    vector<int> a;
    int dp[1010][2];
    int rec(int i, int end) {
        if (n == 1) return a[0];
        int e = ((end == 0) ? n-1 : n);
        if (i >= e) return 0;
        if(dp[i][end] != -1) {
            return dp[i][end];
        }
        int ans = 0;
        ans = max(ans, a[i] + rec(i+2, end));
        ans = max(ans, rec(i+1, end));

        return dp[i][end] = ans;
    }

    int rob(vector<int>& nums) {
        n = nums.size();
        a = nums;
        memset(dp,-1,sizeof(dp));
        int res1 = rec(0, 0);
        int res2 = rec(1, 1);
        
        return max(res1, res2);
    }
};
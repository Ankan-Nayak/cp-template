// dp[i] = no of continuous 1 finishes at i th row

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int m = matrix[0].size();

        vector<vector<int>> a(n, vector<int> (m, 0));
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                if (matrix[i][j] == 1) {
                    a[i][j] = ((i > 0) ? a[i-1][j] + 1 : 1);
                } else {
                    a[i][j] = 0;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i) {
            cout << "i " << i << endl;
            priority_queue<int, vector<int>, greater<int>> pq;
            for (int j = 0; j < m; ++j) {
                pq.push(a[i][j]);
            }
            while (!pq.empty()) {
                ans = max(ans, (int)pq.size() * pq.top());
                pq.pop();
            }        
        }

        return ans;
        
    }
};
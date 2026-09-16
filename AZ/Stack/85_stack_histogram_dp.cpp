class Solution {
public:
    int n, m;
    int height[205][205];
    vector<int> NSE(vector<int> v) {
        vector<int> nse(v.size());
        stack<int> st;
        for (int i = 0; i < v.size(); ++i) {
            while (!st.empty() && v[i] < v[st.top()]) {
                nse[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        while (!st.empty()) {
            nse[st.top()] = v.size();
            st.pop();
        }
        return nse;
    }

    vector<int> PSE(vector<int> v) {
        vector<int> pse(v.size());
        stack<int> st;
        for (int i = v.size() - 1; i >= 0; --i) {
            while (!st.empty() && v[i] < v[st.top()]) {
                pse[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        while (!st.empty()) {
            pse[st.top()] = -1;
            st.pop();
        }
        return pse;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        n = matrix.size();
        m = matrix[0].size();

        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                int x = ((matrix[i][j] == '1') ? 1 : 0);
                if (x == 1) height[i][j] = x + ((i > 0) ? height[i-1][j] : 0);
                else height[i][j] = 0;
            }
        }

        int res = 0;
        for (int i = 0; i < n; ++i) {
            vector<int> h;
            for (int j = 0; j < m; ++j) {
                h.push_back(height[i][j]);
            }
            vector<int> nse = NSE(h);
            vector<int> pse = PSE(h);

            for (int j = 0; j < m; ++j) {
                int r = nse[j];
                int l = pse[j];
                
                int area = height[i][j] * (r - l - 1);
                res = max(res, area);
            }
        }
        return res;
    }
};
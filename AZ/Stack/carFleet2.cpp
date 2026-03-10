class Solution {
public:
    vector<double> getCollisionTimes(vector<vector<int>>& cars) {
        stack<int> st;
        vector<double> ans(cars.size(), -1);
        for (int i = cars.size() - 1; i >= 0; --i) {
            while (!st.empty() && cars[i][1] <= cars[st.top()][1]) { // want lowest speed
                st.pop();
            }

            int p1 = cars[i][0], sp1 = cars[i][1];
            while(!st.empty()) {
                double time = (double)(cars[st.top()][0] - cars[i][0]) / (cars[i][1] - cars[st.top()][1]);
                if (time < ans[st.top()] || ans[st.top()] == -1) {
                    ans[i] = time;
                    break;
                }
                st.pop();
            }
            st.push(i);
        }
        return ans;
    }
};

// (p1, s1), (p2, s2) => (p1 < p2) & (s1 > s2)
// (p1 + s1 * t) = (p2 + s2 * t) 
// time = (p1 - p2) / (s2 - s1);
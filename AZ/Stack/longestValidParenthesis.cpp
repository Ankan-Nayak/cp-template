class Solution {
public:
    int longestValidParentheses(string s) {
        map<char, int> mp;
        mp['('] = 1;
        mp[')'] = -1;

        int ans = 0, cur = 0, l = -1;
        stack<int> st;
        stack<int> idx;
        idx.push(-1);
        for (int i = 0; i < s.size(); ++i) {
     
            int x = mp[s[i]];
            if (x == 1) {
                st.push(x);
                idx.push(i);
            } else {
                if (!st.empty() && st.top() == 1) {
                    st.pop();
                    idx.pop();

                    cout << l << endl;
                    ans = max(ans, i - idx.top());
                } else {
                    idx.push(i);
                    while (!st.empty()) {
                        st.pop();
                    }
                }
            }
        }

        return ans;
    }
};
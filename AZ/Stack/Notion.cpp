class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        stack<string> st;

        for (int i = 0; i < n; ++i) {
            if (tokens[i] == "/" || tokens[i] == "*" || tokens[i] == "+" || tokens[i] == "-") {
                int right = stoi(st.top());
                st.pop();

                int left = stoi(st.top());
                st.pop();

                if (tokens[i] == "/") {
                    int res = left / right;
                    st.push(to_string(res));
                } else if (tokens[i] == "*") {
                    int res = left * right;
                    st.push(to_string(res));
                } else if (tokens[i] == "+") {
                    int res = left + right;
                    st.push(to_string(res));
                } else if (tokens[i] == "-") {
                    int res = left - right;
                    st.push(to_string(res));
                }
            } else {
                st.push(tokens[i]);
            }
        }

        int ans = stoi(st.top());
        return ans;
    }
};
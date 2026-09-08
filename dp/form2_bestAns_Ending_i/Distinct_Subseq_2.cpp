class Solution {
public:
    const int m = 1e9+7; 
    int distinctSubseqII(string s) {
        int n = s.size();
        vector<long long> dp(n + 1);
        vector<long long> last(26);
        vector<long long> pref(n + 1);

        dp[0] = 1;
        pref[0] = 1;
        for (int i = 1; i <= n; ++i) {
            char ch = s[i - 1];
            dp[i] = pref[i - 1];

            if (last[ch - 'a'] > 0) {
                int prev = last[ch - 'a'];
                dp[i] -= pref[prev - 1];
            }
            dp[i] = (dp[i] + m) % m;
            pref[i] = (pref[i - 1] + dp[i] + m) % m;
            last[ch - 'a'] = i;
        }
        return (pref[n] - 1 + m) % m;
    }
};


class Solution {
public:
    set<string> st;

    void solve(int i, string &s, string cur) {
        if (i == s.size()) {
            st.insert(cur);
            return;
        }

        // Don't take s[i]
        solve(i + 1, s, cur);

        // Take s[i]
        solve(i + 1, s, cur + s[i]);
    }

    int distinctSubseqII(string s) {
        solve(0, s, "");

        st.erase("");

        return st.size();
    }
};
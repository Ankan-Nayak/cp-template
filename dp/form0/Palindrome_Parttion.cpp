class Solution {
public:
    vector<int> cur;
    vector<vector<int>> a;
    void rec(string s, int i) {
        if (i == s.size()) {
            a.push_back(cur);
            return;
        }
        for (int j = i; j < s.size(); ++j) {
            if (pal(s, i, j)) {
                // cout << i << ' ' << j << endl;
                cur.push_back(j);
                rec(s, j+1);
                cur.pop_back();
            }
        }
    }

    bool pal(string s, int x, int y) {
        for (int i = 0; i < (y - x + 1) / 2; ++i) {
            if (s[i+x] != s[y-i]) return false;
        }
        return true;
    }
    vector<vector<string>> partition(string s) {
        rec(s, 0);
        // cout << pal(s,1,2) << endl;
        vector<vector<string>> ans;
        for (auto it : a) {
            vector<int> temp = it;
            int prev = 0;
            vector<string> b;
            for (int i = 0; i < temp.size(); ++i) {
                // cout << temp[i] << ' ';
                b.push_back(s.substr(prev, (temp[i] - prev + 1)));
                prev = temp[i] + 1;
            }
            // cout << endl;
            ans.push_back(b);
        }
        return ans;
    }
};
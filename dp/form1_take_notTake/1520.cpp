class Solution {
public:
    int n;
    int first[26], last[26];
    int res[100005];
    string ss;
    int func(int l) {
        int start = l;
        int end = last[ss[l] - 'a'];

        for (int i = start; i <= end; i++) {
            if (first[ss[i] - 'a'] < start)
                return 1; // invalid

            end = max(end, last[ss[i] - 'a']);
        }

        res[start] = end;
        return 0;
    }
    
    vector<pair<int, int>> p;
    vector<string> path;
    void buildPath(int i) {
        if (i >= n) return;
        int notTake = rec(i+1);
        int take = 0;
        if (res[i] != -1) {
            take = 1 + rec(res[i]+1);
        }
        if (take > notTake) {
            p.push_back({i, res[i]});
            buildPath(res[i]+1);
        } else {
            buildPath(i+1);
        }
    }

    int dp[100005];
    int rec(int i) {
        if (i >= n) return 0;
        if (dp[i] != -1) return dp[i];
        int ans = 0;
        ans = max(ans, rec(i+1));
        if (res[i] != -1) {
            ans = max(ans, 1 + rec(res[i]+1));
        }
        return dp[i] = ans;
    }
    vector<string> maxNumOfSubstrings(string s) {
        n = s.size();
        ss = s;
        memset(first, -1, sizeof(first));
        memset(last, -1, sizeof(last));
        memset(dp, -1, sizeof(dp));
        memset(res, -1, sizeof(res));

        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            if (first[ch - 'a'] == -1) {
                first[ch - 'a'] = i;
                last[ch - 'a'] = i;
            } else {
                last[ch - 'a'] = i;
            }
        }

        for (int i = 0; i < 26; ++i) {
            if (first[i] == -1) continue;
            int ans = func(first[i]);
        }

        int ans = rec(0);
        cout << ans << endl;

        buildPath(0);

        for (auto [l, r] : p) {
            cout << l << ' ' << r << endl;
            path.push_back(ss.substr(l, r - l + 1));
        }
        return path;
    }
};

/*
if i take a range freq of all elemets has to there, so stre freq of elements
skip option -> i+1
max no -> so max(ans, 1+...)
for all cond -> valid cond go and check 
has to be contineous segment
dp[i] ?
other state -> prev taken, is it still going ? or char[] as state
store end of all chars, as if i decide to take something, take end of it

*/
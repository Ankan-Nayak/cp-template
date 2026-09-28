class Solution {
public:

    // struct segment {
    //     int dist;
    //     int l;
    //     int r;
    //     int level;
    // }

    // start -> {end, level}
    map<int, pair<int, int>> mp;
    void insertInterval(int l, int r, int level) {
        while (l <= r) {
            auto it  = mp.lower_bound(l);
            if (it != mp.begin())  {
                auto prv = prev(it);
                if (prv->second.first >= l) {
                    l = prv->second.first + 1;
                    continue;
                }
            }

            if (it == mp.end() || it->first > r) {
                mp[l] = {r, level};
                return;
            }
            int newR = it->first - 1;

            if (l <= newR) {
                mp[l] = {newR, level};
            }

            l = it->second.first + 1;
        }
    }

    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = intervals.size(), level = 1;
        vector<array<int,4>> v;
        for (int i = 0; i < n; ++i) {
            int l = intervals[i][0], r = intervals[i][1];
            int dist = r - l + 1;
            v.push_back({dist, l, r, 0});
        }
        sort(v.begin(), v.end());
        for (int i = 0; i < n; ++i) {
            v[i][3] = i + 1;
        }
        for (auto &[dist, l, r, level] : v) {
            insertInterval(l, r, level);
        }

        int q = queries.size();
        vector<int> answer;
        for (int i = 0; i < q; ++i) {
            auto it = mp.upper_bound(queries[i]);
            if (it == mp.begin()) {
                answer.push_back(-1);
            } else {
                --it;
                if (it->second.first >= queries[i]) {
                    int level = it->second.second;
                    auto &org = v[level-1];
                    int d = org[2] - org[1] + 1;
                    answer.push_back(d);
                } else {
                    answer.push_back(-1);
                }
            }
        }
        return answer;
    }
};
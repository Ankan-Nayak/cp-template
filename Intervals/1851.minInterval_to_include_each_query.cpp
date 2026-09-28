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


class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        sort(intervals.begin(), intervals.end());
        vector<pair<int,int>> q;
        for (int i = 0; i < queries.size(); ++i) {
            q.push_back({queries[i], i});
        }
        // query, index
        sort(q.begin(), q.end());
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // len, endIndex

        vector<int> ans(q.size(), -1);
        int j = 0;
        for (int i = 0; i < q.size(); ++i) {
            while (!pq.empty() && pq.top().second < q[i].first) {
                pq.pop();
            }
            while (j < intervals.size() && intervals[j][0] <= q[i].first) {
                if (intervals[j][1] >= q[i].first) {
                    pq.push({intervals[j][1] - intervals[j][0] + 1, intervals[j][1]});
                }
                j += 1;
            }
            if (!pq.empty()) ans[q[i].second] = pq.top().first;
        }
        return ans;
    }
};
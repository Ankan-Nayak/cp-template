class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());

        // start, end
        map<int, int> mp;
        for (int i = 0; i < intervals.size(); ++i) {
            int l = intervals[i][0], r = intervals[i][1], newL, newR;
            auto it = mp.lower_bound(l);

            /*  ________________
                   ________
            */ 


            /*   will not reach as sorted order
                ________________
               ________
            */ 

            /* ________________
                           ________
            */ 


            /*   will not reach as sorted order
                ________________
              _________________________
            */ 

            if (it == mp.begin()) { // no element inserted
                mp[l] = r;
                continue;
            }

            auto prv = prev(it);
            if (it == mp.end()) {
                if (prv->second >= l) {
                    newL = prv->first, newR = max(r, prv->second);
                    mp.erase(prv);
                } else {
                    newL = l, newR = r;
                }
                mp[newL] = newR;
                continue;
            }

            mp.erase(it);
            mp[l] = r;

        }
        vector<vector<int>> ans;
        for (auto it : mp) ans.push_back({it.first, it.second});
        return ans;
    }
};


class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {

        sort(intervals.begin(), intervals.end());

        vector<vector<int>> ans;

        for (const auto& interval : intervals) {

            // Overlapping intervals → merge them
            if (!ans.empty() && interval[0] <= ans.back()[1]) {
                ans.back()[1] = max(ans.back()[1], interval[1]);
            }
            // Non-overlapping interval → add separately
            else {
                ans.push_back(interval);
            }
        }

        return ans;
    }
};
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

/*We can see that we can maintain candidate cars in this way using a stack, 
removing cars with speed greater than or equal to current car, 
and then removing cars which can never be first point of intersection. The first car after this process (if any) would be first point of intersection.*/





//car fleet 1
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        int n = speed.size();
        vector<pair<int, int>> a;
        for (int i = 0; i < n; ++i) {
            a.push_back({position[i], speed[i]});
        }
        sort(a.begin(), a.end());
        stack<int> st;
        vector<int> ans(n+1);
        for (int i = 0; i < n; ++i) {
            if (!st.empty() && a[st.top()].second <= a[i].second) {
                // skip -> ct++
            }

            while (!st.empty() && a[st.top()].second > a[i].second) {
                long double netDist = a[i].first - a[st.top()].first;
                long double netSpeed = a[st.top()].second - a[i].second;
                long double time = netDist / netSpeed;

                if (a[i].first + (time * a[i].second) <= target) {
                    st.pop();
                } else {
                    break;
                }
            }
            
            st.push(i);
       
        }
        return st.size();
    }
};


/*
0 3 5 8 10
1 3 1 4 2

cur sp = x, next sp = y (y>=x)
unable to catch beacuse of sp and dist
*/
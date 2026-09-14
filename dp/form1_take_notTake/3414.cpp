class Solution {
public:
    int n;
    vector<vector<int>> a;

    long long dp[50001][5];
    vector<int> pathh[50001][5];
    long long rec(int i, int len) {
        if (i >= n || len >= 4)
            return 0;

        if (dp[i][len] != -1)
            return dp[i][len];


        // ---------------- TAKE ----------------
        auto it = upper_bound(
            a.begin(),
            a.end(),
            a[i][1],
            [](int x, const vector<int>& v) {
                return x < v[0];
            }
        ) - a.begin();

        long long takeScore = a[i][2] + rec(it, len + 1);

        // Copy at most 3 elements
        pathh[i][len] = pathh[it][len + 1];

        // Add current original index
        pathh[i][len].push_back(a[i][3]);

        // Manual insertion into sorted path
        for (int j = (int)pathh[i][len].size() - 1; j > 0; --j) {
            if (pathh[i][len][j] < pathh[i][len][j - 1])
                swap(pathh[i][len][j], pathh[i][len][j - 1]);
            else
                break;
        }


        // ---------------- SKIP ----------------
        long long skipScore = rec(i + 1, len);

        // ---------------- CHOOSE ----------------
        if (takeScore > skipScore) {
            dp[i][len] = takeScore;
        }
        else if (takeScore < skipScore) {
            dp[i][len] = skipScore;
            pathh[i][len] = pathh[i + 1][len];
        }
        else {
            // Same score.
            // pathh[i][len] currently contains TAKE path.
            if (pathh[i + 1][len] < pathh[i][len]) {
                pathh[i][len] = pathh[i + 1][len];
            }
            dp[i][len] = takeScore;
        }
        return dp[i][len];
    }



    // vector<int> p;
    // void path(int i, int len) {
    //     if (i >= n) {
    //         return;
    //     }
    //     if (len == 4) {
    //         return;
    //     }
    //     long long a1 = 0, a2 = 0;
    //     if (len < 4) {
    //         auto it = upper_bound(a.begin(), a.end(), a[i][1],[&](int x, vector<int>v){
    //             return x < v[0];
    //         }) - a.begin();
    //         a1 = max(a1, a[i][3] + rec(it, len+1));
    //     }

    //     a2 = max(a2, rec(i+1, len));

    //     if (a1 >= a2 && len < 4) {
    //         p.push_back(a[i][2]);
    //         auto it = upper_bound(a.begin(), a.end(), a[i][1],[&](int x, vector<int>v){
    //             return x < v[0];
    //         }) - a.begin();
    //         path(it, len+1);
    //     } else {
    //         path(i+1, len);
    //     }
    // }
    
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        memset(dp, -1, sizeof(dp));
        int sz = intervals.size();
        n = sz;
        for (int i = 0; i < sz; ++i) intervals[i].push_back(i);

        // sort(intervals.begin(), intervals.end(),[&](
        //     vector<int>a, vector<int>b){return a[1] < b[1]});

        sort(intervals.begin(), intervals.end());
        a = intervals;

        long long res = rec(0,0);
        return pathh[0][0];

    }
};

/*
i can take or avoid
sort based on start pos
sort based on end pos

keep track of only 4 elements -> after taking one can call upper bound
store pos also in parameter to track later

Time Complexity -> 0(n) or 0(nlogn)
can we store upto pos i, max score for len 1,2,3,4 dp[i][len]

*/
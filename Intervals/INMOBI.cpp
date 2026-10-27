#include <bits/stdc++.h>
using namespace std;

#define int long long

int ct = 0, sum = 0, Budget, ans = 0;
vector<int> Cost;
set<pair<int,int>> taken, rest;   // (cost, id) is unique, so set works

void fixUp() {
    // 1. invariant: every taken <= every rest
    while (!rest.empty() && !taken.empty() && *rest.begin() < *taken.rbegin()) {
        auto a = *rest.begin();
        auto b = *taken.rbegin();
        rest.erase(rest.begin());
        taken.erase(prev(taken.end()));
        taken.insert(a);
        rest.insert(b);
        sum += a.first - b.first;
    }
    // 2. over budget: push the most expensive taken back to rest
    while (sum > Budget) {
        auto it = prev(taken.end());
        auto a = *it;
        taken.erase(it);
        rest.insert(a);
        sum -= a.first;
        ct--;
    }
    // 3. grow: pull in the cheapest rest while it fits
    while (!rest.empty() && sum + rest.begin()->first <= Budget) {
        auto it = rest.begin();
        auto a = *it;
        rest.erase(it);
        taken.insert(a);
        sum += a.first;
        ct++;
    }
}

void removeMachine(int id) {
    pair<int,int> p = {Cost[id], id};
    auto it = taken.find(p);
    if (it != taken.end()) {
        taken.erase(it);
        ct--;
        sum -= Cost[id];
    } else {
        rest.erase(p);
    }
}

void addMachine(int id) {
    rest.insert({Cost[id], id});
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n >> Budget;

        // reset all state per test case
        taken.clear();
        rest.clear();
        ct = sum = ans = 0;

        vector<int> st(n), en(n);
        Cost.assign(n, 0);
        for (auto &x : st) cin >> x;
        for (auto &x : en) cin >> x;
        for (auto &x : Cost) cin >> x;

        vector<tuple<int,int,int>> ev;
        for (int i = 0; i < n; i++) {
            ev.push_back({st[i], 1, i});
            ev.push_back({en[i] + 1, -1, i});   // -1 sorts before 1: removals first
        }
        sort(ev.begin(), ev.end());

        int i = 0;
        while (i < ev.size()) {
            int t = get<0>(ev[i]);
            while (i < ev.size() && get<0>(ev[i]) == t) {
                auto [tm, verdict, id] = ev[i];   // destructure INSIDE the loop
                if (verdict == -1) removeMachine(id);
                else addMachine(id);
                i++;
            }
            fixUp();                 // once per group, after all changes
            ans = max(ans, ct);
        }
        cout << ans << "\n";
    }
    return 0;
}
/*
 * WRITE STUFFS DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */



 /*
 
 You have n machines. Machine i runs during the interval [start[i], end[i]] and costs cost[i] to run. You have a budget B.

Choose a set of machines whose total cost is at most B. Maximize the number of machines that are running at the same time (peak concurrency) among the chosen set.

Input

n, the number of machines
Arrays start[], end[], cost[]
B, the budget

Output: the maximum number of machines that can be running simultaneously without exceeding the budget.

Likely constraints

1 ≤ n ≤ 10^5
1 ≤ B ≤ 10^14
1 ≤ start[i] ≤ end[i] ≤ 10^9
1 ≤ cost[i] ≤ 10^9

Note that n × max cost = 10^5 × 10^9 = 10^14, which matches your budget bound. That suggests costs are summed, so you need 64-bit integers.

Example

n = 4, B = 10
start = [1, 2, 3, 6]
end   = [5, 6, 7, 8]
cost  = [4, 3, 5, 2]
At time 3–5, machines 1, 2 and 3 overlap, with cost 4+3+5 = 12 > 10.
Pick machines 1 and 2 (cost 7), so 2 run at once.
Machines 2 and 4 overlap at time 6 with cost 5, which also gives 2.
Answer: 2

*/
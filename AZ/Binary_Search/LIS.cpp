int LIS(vector<int>& a) {
    vector<int> temp;

    for (int x : a) {
        // find first element >= x
        auto it = lower_bound(temp.begin(), temp.end(), x);

        if (it == temp.end()) {
            // x is bigger than all elements → extend LIS
            temp.push_back(x);
        } else {
            // replace to keep smallest possible tail
            *it = x;
        }
    }

    return temp.size();
}


// a = [10, 9, 2, 5, 3, 7, 101, 18]
// LIS length = 4  (2, 3, 7, 101)
// 0(NlogN)


// | Requirement             | Binary Search         |
// | ----------------------- | --------------------- |
// | **Strictly Increasing** | `lower_bound` (≥ x) ✔ |
// | **Non-Decreasing**      | `upper_bound` (> x) ✔ |

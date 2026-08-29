#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    vector<int> lis;
    // if len is same take with ending lowest value [1,3,5] > [1,2,9]
    // if diff len take the longest len [1,4,8,9] > [1,7,9]
    vector<int> insertedat(n);

    // Find LIS length using Binary Search
    for (int i = 0; i < n; i++) {

        if (lis.empty() || arr[i] > lis.back()) {
            lis.push_back(arr[i]);

            // if some value is increasing the size of list i get it it's part of the ans
            insertedat[i] = lis.size() - 1;
        }
        else {
            auto it = lower_bound(lis.begin(), lis.end(), arr[i]);

            *it = arr[i];

            insertedat[i] = it - lis.begin();
        }
    }

    // LIS length
    cout << lis.size() << endl;

    // Reconstruct LIS
    int curLen = lis.size() - 1;
    vector<int> final_lis;

    for (int i = n - 1; i >= 0; i--) {
        if (insertedat[i] == curLen) {
            final_lis.push_back(arr[i]);
            curLen--;
        }
    }

    // We found it backwards
    reverse(final_lis.begin(), final_lis.end());

    // Print LIS
    for (int x : final_lis)
        cout << x << " ";

    cout << endl;

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, target;
    cin >> n >> target;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());

    int cnt = 0;

    for (int j = 0; j < n; j++) {
        int i = 0;
        int k = n - 1;

        while (i < j && j < k) {
            int sum = arr[i] + arr[j] + arr[k];

            if (sum == target) {
                int itemp = i;
                int ktemp = k;

                while (itemp < j && arr[itemp] == arr[i]) itemp++;
                while (ktemp > j && arr[ktemp] == arr[k]) ktemp--;

                cnt += (itemp - i) * (k - ktemp);

                i = itemp;
                k = ktemp;
            }
            else if (sum < target) {
                i++;
            }
            else {
                k--;
            }
        }
    }

    cout << cnt << "\n";
    return 0;
}
#include<bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);

    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vector<int> a(n + 1), left(n + 2), right(n + 2, n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        stack<int> st, skt;
        for (int i = n; i >= 1; --i) {
            if (!st.empty()) {
                while (!st.empty()  &&  a[st.top()] > a[i]) {
                    left[st.top()] = i;
                    st.pop();
                }
            } 
            st.push(i);
        }

        for (int i = 1; i <= n; ++i) {
            if (!skt.empty()) {
                while (!skt.empty()  &&  a[skt.top()] > a[i]) {
                    right[skt.top()] = i;
                    skt.pop();
                }
            } 
            skt.push(i);
        }
        

        int max_area = 0;
        for (int i = 1; i <= n; ++i) {
            max_area = max(max_area, a[i] * (right[i] - left[i] - 1));
        }
        cout << max_area << endl;
    }

    return 0;
}

// Golden Rules
/*
    Solutions are simple.
 
    Proofs are simple.
 
    Implementations are simple.
*/
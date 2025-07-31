#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9 + 7;

int sum = 0, sumsq = 0, cnt = 0;

// frequency
map<int, int> freq; // value → count
map<int, set<int>> freq_to_values; // count → set of values

// median
multiset<int> low, high;

// Modular Inverse
int modinv(int a, int mod = MOD) {
    int res = 1, p = mod - 2;
    while (p) {
        if (p & 1) res = res * a % mod;
        a = a * a % mod;
        p >>= 1;
    }
    return res;
}

// Balance median heaps
void balance() {
    while (low.size() < high.size()) {
        int x = *high.begin();
        high.erase(high.find(x));
        low.insert(x);
    }
    while (low.size() > high.size() + 1) {
        int x = *low.rbegin();
        low.erase(low.find(x));
        high.insert(x);
    }
}

// Insert x
void insert(int x) {
    sum += x;
    sumsq += x * x;
    cnt++;

    int ct = freq[x];
    if (ct > 0) {
        freq_to_values[ct].erase(x);
        if (freq_to_values[ct].empty()) freq_to_values.erase(ct);
    }
    freq[x]++;
    freq_to_values[ct + 1].insert(x);

    if (low.empty() || x <= *low.rbegin()) low.insert(x);
    else high.insert(x);
    balance();
}

// Remove x
void remove(int x) {
    sum -= x;
    sumsq -= x * x;
    cnt--;

    int ct = freq[x];
    freq_to_values[ct].erase(x);
    if (freq_to_values[ct].empty()) freq_to_values.erase(ct);
    freq[x]--;
    if (freq[x] > 0)
        freq_to_values[ct - 1].insert(x);

    if (low.find(x) != low.end()) low.erase(low.find(x));
    else high.erase(high.find(x));
    balance();
}

// Mean
int getMeanResult() {
    int P = sum % MOD;
    int Q = cnt;
    int Qinv = modinv(Q);
    return (P * Qinv) % MOD;
}

// Median
int getMedianResult() {
    if ((low.size() + high.size()) % 2) {
        return *low.rbegin() % MOD;
    } else {
        int a = *low.rbegin();
        int b = *high.begin();
        int P = (a + b) % MOD;
        int Qinv = modinv(2);
        return (P * Qinv) % MOD;
    }
}

// Mode
int getModeResult() {
    int maxFreq = freq_to_values.rbegin()->first;
    int smallestVal = *freq_to_values.rbegin()->second.begin();
    return smallestVal;
}

double variance(int x) {
    // Population variance:
    // σ² = ∑(xi - μ)² / N
    // => σ² = (∑x² / N) - μ²
    // Where:
    //   - ∑x² = sumsq
    //   - ∑x  = sum
    //   - μ = sum / N

    double mean = 1.0 * sum / cnt;
    double avg_sumsq = 1.0 * sumsq / cnt;
    return avg_sumsq - mean * mean;
}


// Reset between test cases
void reset() {
    sum = sumsq = cnt = 0;
    freq.clear();
    freq_to_values.clear();
    low.clear();
    high.clear();
}

// Main
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int T;
    cin >> T;
    while (T--) {
        int Q;
        cin >> Q;
        reset();
        while (Q--) {
            string cmd;
            cin >> cmd;
            if (cmd == "insert") {
                int x; cin >> x;
                insert(x);
            } else if (cmd == "remove") {
                int x; cin >> x;
                remove(x);
            } else if (cmd == "getMean") {
                if (cnt == 0) cout << -1 << '\n';
                else cout << getMeanResult() << '\n';
            } else if (cmd == "getMedian") {
                if (cnt == 0) cout << -1 << '\n';
                else cout << getMedianResult() << '\n';
            } else if (cmd == "getMode") {
                if (cnt == 0) cout << -1 << '\n';
                else cout << getModeResult() << '\n';
            }
        }
    }

    return 0;
}

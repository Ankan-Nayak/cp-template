// iterative dp with mod , 0(N)
#include <iostream>
using namespace std;

const int MOD = 1e9 + 7;
long long der[1000001];

void compute_derangements(int N) {
    der[1] = 0, der[2] = 1;
    for (int i = 3; i <= N; i++) {
        der[i] = ((i - 1) * (der[i - 1] + der[i - 2])) % MOD;
    }
}

int main() {
    int N;
    cin >> N;
    compute_derangements(N);
    cout << der[N] << endl;
    return 0;
}


// recursive 2^N , use recursive dp
#include <iostream>
using namespace std;

long long derangement(int n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    return (n - 1) * (derangement(n - 1) + derangement(n - 2));
}

int main() {
    int n;
    cin >> n;
    cout << derangement(n) << endl;
    return 0;
}

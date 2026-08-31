#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, m, k;
int dp[35][35][55];
const int inf = 1e18;

int rec(int N, int M, int K) {
    if (K == 0) return 0;
    if (N * M == K) return 0;
    if (N*M < K) return inf;
    if (dp[N][M][K] != -1) return dp[N][M][K];
    int res = inf;
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j <= K; ++j) {
            res = min(res, rec(i, M, j) + rec(N-i, M, K-j) + (M * M));
        }
    }
    for (int i = 1; i < M; ++i) {
        for (int j = 0; j <= K; ++j) {
            res = min(res, rec(N, i, j) + rec(N, M-i, K-j) + (N * N));
        }
    }
    return dp[N][M][K] = res;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(dp, -1, sizeof(dp));

    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m >> k;
        cout << rec(n, m, k) << endl;
    }

    return 0;
}
/*
N items
x1, x2...xn
find subset if exist sum = Target

dp(level, s) = dp(level + 1 sumTaken) or dp(level + 1, sumtaken + a[level])*/

#include<bits/stdc++.h>
using namespace std;

int n;
int t;
int x[100];
int dp[100][10000];

int rec(int level, int taken) {
	if (taken > t) {
		return 0;
	}
	if (level == n+1) {
		if (t == taken) {
			return 1;
		} else {
			return 0;
		}
	}
	if (dp[level][taken] != -1) {
		return dp[level][taken];
	}
	int ans = 0;
	if (rec(level + 1, taken) == 1) {
		ans = 1;
	} else if (rec(level + 1, taken + x[level]) == 1) {
		ans = 1;
	}
	return dp[level][taken] = ans;
}

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);


	cin >> n >> t;
	for (int i = 1; i <= n; ++i) {
		cin >> x[i];
	}

	memset(dp, -1, sizeof(dp));
	cout << rec(1, 0);
	
	return 0;
}

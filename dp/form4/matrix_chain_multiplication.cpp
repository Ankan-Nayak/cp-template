



#include<bits/stdc++.h>
using namespace std;


int n;
int x[1010], y[1010]; // this both represent dimension of matrix.


int dp[1010][1010]; // memoization table (fast look-up).
int back[1010][1010]; // to store best mid 


int rec(int l, int r) {
	// pruning
	if(l>r) return 0;
	// basecase
	if(l==r) return 0; // if one matrix, then cost will be 0.
	// cache-check
	if(dp[l][r] != -1) {
		return dp[l][r];
	}
	// compute
	int ans = 1e9; // find min. cost
	for(int mid=l; mid<r; mid++) {
	    int bestmid = rec(l,mid) + rec(mid+1, r) + x[l]*y[mid]*y[r]; // x[l]*y[mid]*y[r] = x[l]*x[mid+1]*y[r]
	    if(bestmid<ans){
	        ans = bestmid; // i know which mid gives me best answer
	        back[l][r] = mid;
	    }
	}
	// save & return
	return dp[l][r] = ans;
}


int opB[101];
int clB[101];

// this is very similar to balanced paranthesis problem, 
// we were solved using backtracking
void generate(int l, int r){
    if(l==r){
        cout<<"A"<<l;
        return;
    }

    opB[l]++;
    clB[r]++;

    int mid = back[l][r];
    cout<<"(";
    generate(l,mid);
    generate(mid+1,r);
    cout<<")";
}


int main() {


	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>x[i]>>y[i];
	}
	memset(dp,-1,sizeof(dp));
	cout << rec(1,n) << endl;
	generate(1,n);

    // or do otherway to print technique
    for (int i = 1; i <= n; ++i) {
        for (int x = 0; x < opB[i]; ++x) {
            cout << "(";
        }
        cout << " " << i << " ";
        for (int x = 0; x < clB[i]; ++x) {
            cout << ")";
        }
    }
}


// input given 1x2, 2x3, 3x4..,that's why no need to check, two nearby matrix is always multiable
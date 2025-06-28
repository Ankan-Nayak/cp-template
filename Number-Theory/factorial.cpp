#include<bits/stdc++.h>
using namespace std;

#define int long long
int mod = 1e9 + 7;

int binpow(int a, int b) {
	if(b == 0) return 1;
	if(b % 2 == 1) return (a * binpow(a, b-1)) % mod;
	else {
		int x = binpow(a, b/2);
		return (x * x) % mod;
	}
}

int inverse(int x) {    // O(log(mod))
	return binpow(x, mod-2);
}

int fact[1000100];
int invfact[1000100];
void precompute_for_faster() {    // O(n) + O(log(mod)) + O(n) ~ O(n + log(mod))
	fact[0] = 1;
	for(int i=1; i<=1000000; i++) {
		fact[i] = (fact[i-1] * i) % mod;
	}
	invfact[1000000] = inverse(fact[1000000]);
	for(int i=1000000; i>=1; i--) {
		invfact[i-1] = (invfact[i] * i) % mod;
	}
}

int ncr_fact_faster(int n, int r) {    // O(1)
	int num = fact[n];
	int den = (invfact[n-r] * invfact[r]) % mod;
	return (num * den) % mod;    // den is already inverted
}

signed main() {
	precompute_for_faster();
	int q;
	cin >> q;

	while(q--) {
		int n, r;
		cin >> n >> r;
		cout << ncr_fact_faster(n, r) << '\n';
	}
	
	return 0;
}



/* dp tabular method
    nCr = (n-1)C(r-1) + nC(r-1)
        1. nth element with previous n-1 elements chose r-1 lements, total 1+(r-1) = r elements
        2. don't chose nth element, from n-1 element chose r elements

        {   r - >
        ^     [1 0 0 0 ..],
        |     [1 1 0 0 ..],
        n     [1 2 1 0 ..]
        }

        a b ..x y
        p q ... z = (x + y)
        ..
*/ 

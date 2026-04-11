#include<bits/stdc++.h>
using namespace std;

struct Query {
	char op;
	int x, y;
};

vector<int> tree;
vector<int> employee, arr;

// update position → mark +1 or -1
void update(int idx, int l, int r, int pos, int addOrRemove) {
    if (l == r) {
		tree[idx] += addOrRemove; // +1, -1
		return;
	}
	int mid = (l + r) / 2;
	if (pos <= mid) {
		update(idx * 2 + 1, l, mid, pos, addOrRemove);
	} else {
		update(idx * 2 + 2, mid + 1, r, pos, addOrRemove);
	}
	tree[idx] = tree[idx * 2 + 1] + tree[idx * 2 + 2];
}

// range sum query
int rangeSumQuery(int idx, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;
	if (l >= ql && r <= qr) return tree[idx];
	int mid = (l + r) / 2;
	return rangeSumQuery(idx * 2 + 1, l, mid, ql, qr) + 
	    	rangeSumQuery(idx * 2 + 2, mid + 1, r, ql, qr); 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		employee.push_back(x);
		arr.push_back(x);
	}



	// vector<array<int, 3>> query;
	// query.push_back({(int)ch, x, y});

    // vector<tuple<char, int, int>> vec;
    // vec.push_back({'a',1,2});
    // auto [type, x, y] = vec[0];

	vector<Query> query;
	for (int i =0 ; i < q; ++i) {
		char op; int x, y;
		cin >> op >> x >> y;
		query.push_back({op, x, y});

		if (op == '?') {
        arr.push_back(x);
        arr.push_back(y);
    }
    if (op == '!') {
        arr.push_back(y);
    }
	}
	
	sort(arr.begin(), arr.end());
	arr.erase(unique(arr.begin(), arr.end()), arr.end());
    int sz = arr.size();

	tree.resize(4 * sz, 0);
	for (int i = 0; i < n; ++i) {
		auto pos = lower_bound(arr.begin(), arr.end(), employee[i]) - arr.begin();
		update(0, 0, sz-1, pos, 1);
	}

	for (int i = 0; i < q; ++i) {

		char op = query[i].op;
		int x = query[i].x, y = query[i].y;

		if (op == '!') {
			int previousValue = employee[x - 1];
			auto pos1 = lower_bound(arr.begin(), arr.end(), previousValue) - arr.begin();
			update(0, 0, sz-1, pos1, -1); // remove

			employee[x - 1] = y;
			auto pos2 = lower_bound(arr.begin(), arr.end(), y) - arr.begin();
			update(0, 0, sz-1, pos2, 1); // add
		}

		if (op == '?') {
			auto R = upper_bound(arr.begin(), arr.end(), y) - arr.begin() - 1;
			auto L = lower_bound(arr.begin(), arr.end(), x) - arr.begin();

			cout << ((L <= R) ? rangeSumQuery(0, 0, sz-1, L, R) : 0) << '\n';
		}
	}

    return 0;
}

/*
Coordinate Decomposition
1 <= a,b <= 1e9, sotring 1-1e9 is not possible
but 1 <= N <= 1e5
just take all possible values, including the queries, which is max 1e5+1e5=2e5
sort them and assign them index, just use Segment tree in index
ie. 1, 17, 9, 13 [no need for 1-17]
sort -> 1, 9, 13, 17 
index -> 0, 1, 2, 3 [work is done in 4]
*/
/*
Given a sequence of n numbers a1, a2 ... an and a number of k-queries. 
A k-query is a triple (i, j, k) (1 ≤ i ≤ j ≤ n). For each k-query (i, j, k), 
you have to return the number of elements greater than k in the subsequence ai, ai+1 ... aj.

solve like this k1 > k2 > k3... for k3 all prev will be also included in ans
all leaf nodes are index or position
*/

#include<bits/stdc++.h>
using namespace std;

vector<int> tree;
vector<int> arr;
set<int> present;

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

    int n;
    cin >> n;

	arr.resize(n);
	map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
		cin >> arr[i];
		mp[arr[i]].push_back(i);
		present.insert(arr[i]);
	}

	int q;
	cin >> q;
	
	vector<array<int, 4>> query;
	for (int i = 0 ; i < q; ++i) {
		int x, y, k;
		cin >> x >> y >> k;
		x--, y--;
		query.push_back({k, x, y, i});
	}
	
	tree.resize(4 * n, 0);
	sort(query.rbegin(), query.rend());
	vector<int> ans(q, 0);
	priority_queue<int> pq;
	for (auto it : present) pq.push(it);


	for (int i = 0; i < query.size(); ++i) {
		int border = query[i][0];
		while (!pq.empty() && border < pq.top()) {
			vector<int> elements = mp[pq.top()]; 
			for (auto it : elements) update(0, 0, n-1, it, 1);
			pq.pop();
		}
		ans[query[i][3]] = rangeSumQuery(0, 0, n-1, query[i][1], query[i][2]);
	}

	for (int i = 0; i < q; ++i) {
		cout << ans[i] << '\n';
	}

    return 0;
}

/*_________________________________________________________________________________________________*/
// space nlogn, each element atmost logn time
// make sorted list for each node

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> tree;
vector<int> arr;

vector<int> merge(const vector<int>& left, const vector<int>& right) {
    int l = 0, r = 0;
    int n = left.size(), m = right.size();
    
    vector<int> res;
    res.reserve(n + m);
    
    while (l < n && r < m) {
        if (left[l] <= right[r]) {
            res.push_back(left[l]);
            l++;
        } else {
            res.push_back(right[r]);
            r++;
        }
    }
    
    while (l < n) {
        res.push_back(left[l]);
        l++;
    }
    
    while (r < m) {
        res.push_back(right[r]);
        r++;
    }
    
    return res;
}

void build(int idx, int l, int r) {
    if (l == r) {
        tree[idx] = {arr[l]};
        return;
    }
    
    int mid = (l + r) / 2;
    
    build(2 * idx + 1, l, mid);
    build(2 * idx + 2, mid + 1, r);
    
    tree[idx] = merge(tree[2 * idx + 1], tree[2 * idx + 2]);
}

int query(int idx, int l, int r, int ql, int qr, int k) {
    if (r < ql || l > qr) return 0;
    
    if (l >= ql && r <= qr) {
        int total = tree[idx].size();
        int notGreater = upper_bound(tree[idx].begin(), tree[idx].end(), k) - tree[idx].begin();
        return total - notGreater;
    }
    
    int mid = (l + r) / 2;
    
    int left_res  = query(2 * idx + 1, l, mid, ql, qr, k);
    int right_res = query(2 * idx + 2, mid + 1, r, ql, qr, k);
    
    return left_res + right_res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    arr.resize(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    
    tree.resize(4 * n);
    build(0, 0, n - 1);
    
    int q;
    cin >> q;
    
    while (q--) {
        int i, j, k;
        cin >> i >> j >> k;
        i--; j--;
        cout << query(0, 0, n - 1, i, j, k) << '\n';
    }
    
    return 0;
}


/*
build n(log^2)n
query log^n
space nlog
*/
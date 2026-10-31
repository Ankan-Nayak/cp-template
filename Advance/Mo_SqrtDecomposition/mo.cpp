/*
break N len into sqrt(N) segments
total N / sqrt(N) segments

for every query [l,r] find unq elements in that range
Time Complexity = N * sqrt(N)

for every block max triversal is N
so N/sqrt(N) block trivesal is (N / sqrt(N)) * N = n * sqrt(N)

Let's see:
Query	L	R	L/B
Q1	    0	4	0
Q2	    1	6	0
Q3	    2	8	0
Q4	    0	8	0
Q5	    3	5	1

After sorting:
Sorted order	Query	Left block	R
1	            [0,4]	    0       4
2	            [0,8]	    0       8
3	            [1,6]	    0       6
4	            [2,8]	    0       8
5	            [3,5]	    1       5
*/



#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int a[N];
int freq[N];
int distinctCnt = 0;

struct Query {
    int l, r, idx;
};

int B;

bool cmp(Query x, Query y) {

    int blockX = x.l / B;
    int blockY = y.l / B;

    if (blockX != blockY)
        return blockX < blockY;

    return x.r < y.r;
}

void add(int x) {
    if (freq[x] == 0)
        distinctCnt++;

    freq[x]++;
}

void remove(int x) {
    freq[x]--;

    if (freq[x] == 0)
        distinctCnt--;
}

int main() {

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    B = sqrt(n);

    vector<Query> queries(q);

    for (int i = 0; i < q; i++) {
        cin >> queries[i].l >> queries[i].r;

        queries[i].idx = i;
    }

    // Sort queries
    sort(queries.begin(), queries.end(), cmp);

    vector<int> ans(q);

    int curL = 0;
    int curR = -1;

    for (auto query : queries) {

        int L = query.l;
        int R = query.r;

        while (curL > L)
            add(a[--curL]);

        while (curR < R)
            add(a[++curR]);

        while (curL < L)
            remove(a[curL++]);

        while (curR > R)
            remove(a[curR--]);

        ans[query.idx] = distinctCnt;
    }

    // Print answers in original query order
    for (int x : ans)
        cout << x << '\n';

    return 0;
}

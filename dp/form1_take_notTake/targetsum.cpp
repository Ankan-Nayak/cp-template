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




/*Now print the solution
for that you need to cache and keep track
rather than taken keep state = 
dp(level, left) = how much do i left or need to make from the cur level = 0,1 poss or not
start from dp(0, t) to end in dp(n, 0)*/



#include<bits/stdc++.h>
using namespace std;

int n, t;
int x[105];
int dp[105][10005];

int rec(int level, int left) {

    if (left < 0)
        return 0;

    if (level == n + 1) {
        return (left == 0);
    }

    if (dp[level][left] != -1)
        return dp[level][left];

    return dp[level][left] =
        rec(level + 1, left) ||
        rec(level + 1, left - x[level]);
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;

    for (int i = 1; i <= n; i++)
        cin >> x[i];

    memset(dp, -1, sizeof(dp));

    cout << rec(1, t);

    return 0;
}



/*print


// DP(1,16)
// ├── skip 1  -> DP(2,16)
// │   ├── skip 2 -> DP(3,16)
// │   └── take 2 -> DP(3,14)
// │       ├── skip 5 -> DP(4,14)
// │       └── take 5 -> DP(4,9)
// │           ├── skip 9 -> DP(5,9)   = false
// │           └── take 9 -> DP(5,0)   = true
// │
// └── take 1 -> DP(2,15)

which line returning 1, go there
Vivek Gupta diagram*/


/*two ways to print ans
1. Recheck -> which is working use that -> below code
2. Backptr -> if multiple value is working save the optimal*/


#include<bits/stdc++.h>
using namespace std;

int n, t;
int x[105];
int dp[105][10005];

int rec(int level, int left) {

    if (left < 0)
        return 0;

    if (level == n + 1) {
        return (left == 0);
    }

    if (dp[level][left] != -1)
        return dp[level][left];

    return dp[level][left] =
        rec(level + 1, left) ||
        rec(level + 1, left - x[level]);
}


void print(int level, int left) {
    if (level == n + 1 || left == 0)    
            return;

    if (rec(level + 1, left) == 1) {
            // ans = 1;
            // don't take this number
            print(level + 1, left);
    }  else if (rec(level + 1, left - x[level]) == 1) {
            // ans = 1;
            // take this
            cout << x[level] << ' ';
            print(level + 1, left - x[level]);
    }
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;

    for (int i = 1; i <= n; i++)
        cin >> x[i];

    memset(dp, -1, sizeof(dp));

    if (rec(1, t)) {
        print(1,t);
    }

    return 0;
}


/*Backtracking by rechecking:
--------------------------------
At print time:
if(skip works) go skip
else take current

No extra storage needed.



Backpointer Method:
--------------------------------
While computing DP,
store WHICH transition was chosen.

Useful when:
1. Need minimum answer
2. Need maximum answer
3. Need lexicographically smallest
4. Need exact optimal path reconstruction

-------------------------------------------------
Example:
Minimum number of elements needed
to make target sum*/




/*
Backtracking by rechecking:
--------------------------------
At print time:
if(skip works) go skip
else take current

No extra storage needed.



Backpointer Method:
--------------------------------
While computing DP,
store WHICH transition was chosen.

Useful when:
1. Need minimum answer
2. Need maximum answer
3. Need lexicographically smallest
4. Need exact optimal path reconstruction

-------------------------------------------------
Example:
Minimum number of elements needed
to make target sum
-------------------------------------------------
*/

#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9;
int n, t;
int a[105];
int dp[105][10005];
/*
back[level][left]
0 -> skip current
1 -> take current
*/
int backptr[105][10005];
int rec(int level, int left) {
    // invalid
    if(left < 0)
        return INF;
    // all elements finished
    if(level == n + 1) {
        if(left == 0) return 0;
        return INF;
    }

    if(dp[level][left] != -1)
        return dp[level][left];

    // option 1 -> skip
    int skip = rec(level + 1, left);

    // option 2 -> take
    int take = 1 + rec(level + 1, left - a[level]);

    // choose minimum
    if(skip <= take) {
        backptr[level][left] = 0;
        return dp[level][left] = skip;

    } else {
        backptr[level][left] = 1;
        return dp[level][left] = take;
    }
}



void print(int level, int left) {
    if(level == n + 1 || left == 0)
        return;

    // skipped
    if(backptr[level][left] == 0) {
        print(level + 1, left);
    }

    // taken
    else {
        cout << a[level] << ' ';
        print(level + 1, left - a[level]);
    }
}



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> t;
    for(int i=1;i<=n;i++)
        cin >> a[i];

    memset(dp, -1, sizeof(dp));
    int ans = rec(1, t);
    if(ans >= INF) {
        cout << "No subset exists\n";
    } else {
        cout << "Minimum elements = " << ans << '\n';
        cout << "Subset: ";
        print(1, t);
    }
}
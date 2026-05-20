#include <bits/stdc++.h>
using namespace std;
int n;
int target;
vector<int>arr;
int dp[1000][1000];
vector<int>temp;
int isPossible(int idx,int left){
  
 if(left<0)return 0;
  
 if(idx==n)return left==0;
  
 if(dp[idx][left]!=-1)return dp[idx][left];
  
 
 bool take=isPossible(idx+1,left - arr[idx]);
 bool Notake=isPossible(idx+1,left);
  
 return dp[idx][left]=(take || Notake);
  
}

void generate(int level,int left){

  if(level==n){
    for(int &x:temp)cout<<x<<" ";
    cout<<endl;
    return;
  }   
  bool take=isPossible(level+1,left - arr[level]);
  bool Notake=isPossible(level+1,left);
   
  if(take){
    temp.push_back(arr[level]);
    generate(level+1,left-arr[level]);
  }
  else {
    generate(level+1,left);
  }
  return;
   
}


int main(){
 cin>>n>>target;
 arr.resize(n);
  
 for(int &x:arr)cin>>x;
 memset(dp,-1,sizeof(dp));
  
 cout<<isPossible(0,target)<<endl;
 generate(0,target);


         // Reconstruct the solution
        vector<int> result;
        int left = target;
        for (int idx = 0; idx < n; idx++) {
            // Check if we can take current element
            if (left >= arr[idx] && dp[idx + 1][left - arr[idx]]) {
                result.push_back(idx);
                left -= arr[idx];
                continue;
            } else {
                // skip
            }
        }
        for (auto it : result) cout << it << ' ';
  
 return 0;
  
}











#include <bits/stdc++.h>
using namespace std;

int n, target;
vector<int> arr;

int dp[1000][1000];
int choice[1000][1000];   // key addition

int isPossible(int idx, int left) {
    if (left < 0) return 0;
    if (idx == n) return left == 0;

    if (dp[idx][left] != -1)
        return dp[idx][left];

    int take = isPossible(idx + 1, left - arr[idx]);
    int nottake = isPossible(idx + 1, left);

    dp[idx][left] = (take || nottake);

    if (take)
        choice[idx][left] = 1;
    else if (nottake)
        choice[idx][left] = 0;

    return dp[idx][left];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target;
    arr.resize(n);
    for (int &x : arr) cin >> x;

    memset(dp, -1, sizeof(dp));
    memset(choice, -1, sizeof(choice));

    cout << isPossible(0, target) << '\n';

    // reconstruction (simple & deterministic)
    vector<int> temp;
    int idx = 0, left = target;

    while (idx < n && left >= 0) {
        if (choice[idx][left] == 1) {
            temp.push_back(idx);
            left -= arr[idx];
        }
        idx++;
    }

    for (int i : temp) cout << i << ' ';
}


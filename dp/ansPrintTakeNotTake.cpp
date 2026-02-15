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
  
 return 0;
  
}

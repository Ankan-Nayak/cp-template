//  ॐ नमः शिवाय // // JAI BAJARANG BALI //
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define ll unsigned long long
#define int long long
#define lld long double
#define mod 1000000007ll
#define inf (1LL<<60)
#define fast_io ios_base::sync_with_stdio(false);cin.tie(NULL)
using namespace std;
using namespace __gnu_pbds;
typedef tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;//find_by_order // order_of_key
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>ordered_set;//find by order // order of key
int expo(ll a, ll b) {a %= mod; ll res = 1; while (b > 0) {if (b & 1) res = (res * a) % mod; a = (a * a) % mod; b >>= 1;} return res;}
double eps = 1e-7;


vector<vector<int>>v;
vector<int>vis;
vector<int>order, par, pref;
bool is_cycle = 0;


void dfs(int n, int pr){
    vis[n] = 2;
    par[n] = pr;
    for(auto ch: v[n]){
        if(vis[ch] == 1){
            dfs(ch, n);
        }
        else if(vis[ch] == 2){
            is_cycle = 1;
            pref[n]++;
            pref[par[ch]]--;
        }
    }
    vis[n] = 3;
    order.push_back(n);
}


int32_t main() {
    fast_io;int t=1;cin>>t; 
    
    for(int T=0;T<t;T++){
        int n,m ;
        cin>>n>>m;
        v.assign(n+1, vector<int>());
        par.assign(n+1, 0);
        pref.assign(n+1, 0);
        is_cycle = 0;


        for(int i=0;i<m;i++){
            int a, b;
            cin>>a>>b;
            v[a].push_back(b);
            // v[b].push_back(a);
        }     


        vis.assign(n+1, 1);
        for(int i=1;i<=n;i++){
            if(vis[i]==1){
                dfs(i, 0);
            }
        }


        int cnt = 0;
        for(int i= 0; i<order.size(); i++){
            pref[par[order[i]]] += pref[order[i]];
            if(order[i] >1){
                cnt++;
            }
        }
        cout<<(is_cycle?"Yes":"No")<<endl;
    }
    return 0;
}

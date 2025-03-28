/*--------------------------------------Header File----------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
using namespace std;


     // use directly these before Ansh, taken from GFG and Dominator
     // #include <ext/pb_ds/assoc_container.hpp> 
     // #include <ext/pb_ds/tree_policy.hpp> 
     // using namespace __gnu_pbds; 
     // #define ll long long
     // for ordered set , notice less
     // #define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>
     // for ordered multiset , notice less_equal
     // #define ordered_set tree<ll, null_type,less_equal<ll>, rb_tree_tag,tree_order_statistics_node_update> 


//ordered_set st, if face problem see Ansh Gupta medium Article

// Policy Based Data Structure
// Note:Upper Bound would work as lower bound and vice versa
//  Find won't work in less_equal, so use find_by_order(order_of_key(a[i]))
//  To check existence use lower_bound
// multiset, pair set possible -> returns pos & index in set
/*ordered_set <int> a;
a.insert(2);
a.insert(4);
a.insert(3);
a.insert(7);
a.insert(5);
//* find_by_order(k): Returns the address of the element at kth index in the set while using zero-based indexing,
cout << *a.find_by_order(3) << endl; //output is 5

// * order_of_key(k): Returns the number of elements strictly smaller than k.
cout << (a.order_of_key(10)) << endl; //output is 5*/

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;

/*---------------------------------------Data Types--------------------------------------------------------------------------------------------------*/

typedef long long ll;
typedef long double lld;
typedef unsigned long long ull;

/*--------------------------------------Value Initialize----------------------------------------------------------------------------------------------------*/

#define INF 1e18
const ll MOD=1e9+7;
const ll MOD1=998244353;
const int maxN = (int)3e5+10;
const int maxn = (int)2e5+10;
const int N = 26;
const lld pi = 3.14159265358979323846264338327950288419716939937510;

/*------------------------------------------Loop------------------------------------------------------------------------------------------------*/

#define rf(i,n) for(int i=n-1; i>=0; --i)
#define  f(i,n) for(int i=0; i<n; ++i)

/*--------------------------------------Debugging Console----------------------------------------------------------------------------------------------------*/

#ifndef ONLINE_JUDGE
#define debug(x) cerr << #x <<' '; _print(x); cerr << endl;
#else
#define debug(x)
#endif

void _print(ll t) {cerr << t;}
void _print(int t) {cerr << t;}
void _print(string t) {cerr << t;}
void _print(char t) {cerr << t;}
void _print(lld t) {cerr << t;}
void _print(double t) {cerr << t;}
void _print(ull t) {cerr << t;}

template <class T, class V> void _print(pair <T, V> p);
template <class T> void _print(vector <T> v);
template <class T> void _print(set <T> v);
template <class T, class V> void _print(map <T, V> v);
template <class T> void _print(multiset <T> v);
template <class T, class V> void _print(pair <T, V> p) {cerr << '{'; _print(p.first); cerr << ','; _print(p.second); cerr << '}';}
template <class T> void _print(vector <T> v) {cerr << '['; for (T i : v) {_print(i); cerr << ' ';} cerr << ']';}
template <class T> void _print(set <T> v) {cerr << '['; for (T i : v) {_print(i); cerr << ' ';} cerr << ']';}
template <class T> void _print(multiset <T> v) {cerr << '['; for (T i : v) {_print(i); cerr << ' ';} cerr << ']';}
template <class T, class V> void _print(map <T, V> v) {cerr << '['; for (auto i : v) {_print(i); cerr << ' ';} cerr << ']';}
void _print(pbds v) {cerr << '['; for (auto i : v) {_print(i); cerr << ' ';} cerr << ']';}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
ll getRandomNumber(ll l, ll r) {return uniform_int_distribution<ll>(l, r)(rng);} 

/*---------------------------------------FAST INPUT_OUTPUT----------------------------------------------------------------------------------------------------*/

void ankan_nayak_1412(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    /*Debugging print in Error.txt File*/
    #ifndef ONLINE_JUDGE
    freopen("Error.txt", "w", stderr);
    #endif
}

/*-----------------------------------------Number Theory--------------------------------------------------------------------------------------------------*/

// for more precise ans avoid calculating point values(computer can't store perfectly in binary) at firts , use at last
bool isPower(int x, int y){float res1 = log(y) / log(x);return res1==floor(res1);}
ll *fact;void calFact(){fact = new ll[maxN];fact[0]=1;fact[1]=1;for (ll i=2; i<maxN; i++)fact[i] = mod_mul(fact[i-1], i);}
ll gcd(ll a, ll b) { if (b == 0) return a; return gcd(b, a % b);}
ll lcm(ll a, ll b) {return (a * b) / gcd(a, b);}
ll ceil_div(ll a,ll b){return (a+b-1)/b;}
/*use [ sqrtl ] for efficiency*/
ll SQRT(ll a){ll x = sqrt(a)+2; while(x*x>a) x--;return x;}
int floorSqrt(int n) {int low = 1, high = n;while (low <= high) {long long mid = (low + high) / 2;long long val = mid * mid;if (val <= (long long)(n)) {low = mid + 1;}else {high = mid - 1;}}return high;}
float Precision_squareRoot(int x, int precision){int start = 1, end = x;int mid;float ans; while (start <= end) {mid = (start + end) / 2;if (mid * mid == x) {ans = mid;break;}if (mid * mid < x) {start = mid + 1;ans = mid;}else {end = mid - 1;}   }float increment = 0.1;for (int i = 0; i < precision; i++) {while (ans * ans <= x) {   ans += increment;}ans = ans - increment;increment = increment / 10;}return ans;}
ll mod_add(ll a, ll b) {a = a % MOD; b = b % MOD; return (((a + b) % MOD) + MOD) % MOD;}
ll mod_inv(ll i) {if (i == 1) return 1; return mod_power(i,MOD-2);}
ll mod_substraction(ll a, ll b) {return ((a % MOD)-(b % MOD) + MOD) % MOD;}
ll mod_div(ll a, ll b) {a = a % MOD; ll inv = mod_inv(b); if (inv == -1) return -1; else {ll ans = (inv * a) % MOD; return ans;}}
ll mod_mul(ll a, ll b) {a = a % MOD; b = b % MOD; return (((a * b) % MOD) + MOD) % MOD;}
ll mod_inverse(ll i) {if (i == 1) return 1; return (MOD - ((MOD / i) * mod_inv(MOD % i)) % MOD) % MOD;}
ll mod_power(ll a, ll b){a%=MOD;if(b < 0) return 0;ll res = 1;while (b > 0){if (b & 1) res = (res*1ll*a) % MOD;a = (a*1ll*a) % MOD;b >>= 1;}return res;}
ll mod_ans(ll a){return ( a % MOD + MOD ) % MOD ;} /*Negative_MOD*/
ll inverse(ll a){if (a == 1) return 1; return mod_power(a,MOD-2);}
ll Super_Pow(ll a, ll b, ll c) { return mod_power(a,mod_power(b,c/* ,MOD-1 */)/* ,MOD */);}
ll factorial(ll n){return (n==1 || n==0) ? 1 : ( ( n % MOD ) * 1ll* factorial(n-1)) % MOD;}
ll ncr(ll n, ll r){ll ans = fact[n];ans = mod_mul(ans, mod_inv(fact[n - r]));ans = mod_mul(ans, mod_inv(fact[r]));return ans;}
ll npr(ll n, ll r){ll ans = fact[n];ans = mod_mul(ans, mod_inv(fact[n - r]));return ans;}

int nearest_Powerof2_greater_equal(int n){return pow(2, ceil(log(n)/log(2)));}
int highest_Powerof2_less_equal(int n){int p = (int)log2(n);return (int)pow(2, p);}
bool isKthBitSet(ll n, ll k){if ((n >> k) & 1)return true;return false;}
bool isPerfectSquare(int x){if(x >= 0){int sr = sqrt(x);return (sr*sr == x);}return false;}
bool isPowerOfTwo(int n){if(n==0)return false;return (ceil(log2(n)) == floor(log2(n)));} // return x && ~(x&(x-1))
ll max_digit_num(ll x){ll ans=INT_MIN;while(x > 0) ans = max(ans,x%10), x /= 10; return ans;}
ll min_digit_num(ll x){ll ans=INT_MAX;while(x > 0) ans = min(ans,x%10), x /= 10; return ans;}
ll digit_sum(ll x){ll ans=0;while(x > 0) ans += x % 10, x /= 10; return ans;}

long long mod_add(long long a,long long b,long long m){
    return (a % m + b % m) % m;
}
long long mod_minus(long long a,long long b,long long m){
    return (a % m - b % m) % m;
}
long long mod_mul(long long a,long long b,long long m){
    return (a % m * b % m) % m;
}
int nCr_mod2(int n, int r) {
    return ((n & r) == r) ? 1 : 0;
}

// Compute nCr for small n, r (n, r < 5)
// use lucas when mod is small, and high chance %mod == 0, then exp would  not work, lucas will
int nCrSmall(int n, int r) {
    if(r > n) return 0;
    int res = factorial[n];
    res = (res * modInverse(factorial[r], 5)) % 5;
    res = (res * modInverse(factorial[n - r], 5)) % 5;
    return res;
}
// Lucas theorem: recursively compute nCr modulo 5
int nCrLucas(int n, int r) {
    if(r == 0) return 1;
    int n_i = n % 5;
    int r_i = r % 5;
    if(r_i > n_i) return 0;
            return (nCrSmall(n_i, r_i) * nCrLucas(n / 5, r / 5)) % 5;
}
long long binary_expo(long long a,long long b){
    long long ans=1,base=a;
    while(b>0){
        if(b%2==0){
            base=(base*base)%MOD;
            b=b/2;
        }
        else{
            ans=(ans*base)%MOD;
            b=b-1;
        }
    }
    return ans;
}
long long modulo_div(long long a,long long b,long long m){
    return mod_mul(a,binary_expo(b,m-2),m);
}

const int MAXN = 1001;
long long fact[MAXN], invFact[MAXN]; 
long long modExp(long long base, long long exp, long long mod) {
  long long result = 1;
  while (exp > 0) {
      if (exp % 2 == 1) {
          result = (result * base) % mod;
      }
      base = (base * base) % mod;
      exp /= 2;
  }
  return result;
}
// Precompute factorials and modular inverses using Fermat's Little Theorem
void precomputeFactorials() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAXN; ++i) {
        fact[i] = fact[i-1] * i % MOD;
        invFact[i] = modExp(fact[i], MOD-2, MOD); // Fermat's Little Theorem
    }
//inv_fact[N - 1] = power(fact[N - 1], mod - 2); // Compute only once
//for (int i = N - 2; i >= 1; i--) {
//    inv_fact[i] = mul(inv_fact[i + 1], i + 1); // Compute in O(N)
//}
}
// Function to calculate nCr % MOD
long long nCr(int n, int r) {
    if (n < r) return 0;
    return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
}

// new diffrent way when is too big, r is too small (n <= 1e8)

// Compute nCr for (potentially) large n, assuming r is small.
int ncr(int n, int r) {
    if (r > n || r < 0) return 0;
    int z = 1;
    // Multiply the terms in the numerator: n*(n-1)*...*(n-r+1)
    for (int i = n; i >= n - r + 1; i--) {
        z = (z * i) % MOD;
    }
    // Multiply by the modular inverse of r!
    z = (z * invFact[r]) % MOD;
    return z;
}

void pascalTriangle(int n) {
    for (int i = 0; i < n; i++) {
        int val = 1;
        for (int j = 0; j <= i; j++) {
            cout << val << ' '; 
            val = val * (i - j) / (j + 1); // Compute next binomial coefficient
        }
        cout << endl;
    }
}
// table make i = n, j = r, => ncr = table[i][j]
/*-----------------------------------------------Short Cut--------------------------------------------------------------------------------------------*/

#define all(v) v.begin(), v.end()
#define Fill(arr , val) memset(arr , val , sizeof(arr))
//iota(all(v),0)

//v1.insert(v1.end(),v2.begin(),v2.end()); conactonate
//v.resize(distance(v.begin(), unique(v.begin(), v.end())));
//s.find("111") -> -1 or pos 
//s.rfind("111") -> -1 or reverse pos 

/*----------------------------------------------String Related--------------------------------------------------------------------------------------------*/

//to find where code fails use string fromat to find input
//s.find("111") -> -1 or pos 
//s.rfind("111") -> -1 or reverse pos 
//int x = vs[i].find('char you want') < vs[i].length();
//bool x = vs[i].find('char/ string you want') != string :: npos;
//s.erase(unique(s.begin(),s.end()),s.end());
//if(i==0 || x!=v.back()){v.push_back(x);}
//s.erase( remove(s.begin(), s.end(), c) ,s.end()); delete a particular element
//binary conversion ->(bool)(i&(1<<j))!=0
string decimal_to_binary(ll n){ll number=(int)(log2(n)); string s="0"; if(n==0) return s;  else return bitset<64>(n).to_string().substr(64 - number - 1);}
ll isSubstring(string s1, string s2){bool isfound = s2.find(s1) != string::npos;return isfound;}
string LCSubStr_Print(string X, string Y){int m = X.length();int n = Y.length();int result = 0;int end;int len[2][n + 1];int currRow = 0;for (int i = 0; i <= m; i++) {for (int j = 0; j <= n; j++) {if (i == 0 || j == 0) {len[currRow][j] = 0;}else if (X[i - 1] == Y[j - 1]) {len[currRow][j] = len[1 - currRow][j - 1] + 1;if (len[currRow][j] > result) {result = len[currRow][j];end = i - 1;}}else {len[currRow][j] = 0;}}currRow = 1 - currRow;}if (result != 0) {return X.substr(end - result + 1, result);}return to_string(-1);}
ll LCSubStr(string X, string Y, int m, int n){int LCSuff[m + 1][n + 1];int result = 0; for (int i = 0; i <= m; i++){for (int j = 0; j <= n; j++){if (i == 0 || j == 0)LCSuff[i][j] = 0;else if (X[i - 1] == Y[j - 1]) {LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;result = max(result, LCSuff[i][j]);}else LCSuff[i][j] = 0;}}return result;}
//length -> longest common subsecuence string //string X, Y; cin >> X >> Y; int m = X.length();int n = Y.length(); ll res = LCSubStr(X, Y, m, n);

string Decimal_To_Base(int n, int base){
  string s;
  while(n != 0){
    s.push_back((n % base) +'0');
    n /= base;
  }
  reverse(s.begin(), s.end());
  return s;
}

string decimalToBase(int decimal) {
string result = "";
// special case for input 0
if (decimal == 0) {
result = "0";
} else {
// convert decimal to base-9 using modulo operator and integer division
while (decimal != 0) {
int digit = decimal % 9;
result = to_string(digit) + result;
decimal /= 9;
}
}
}

//delete k elements from string to make it lexicographically largest
string lex_lrgst_Str(string s, int k){
  string res;
  for (int i = 0; i < s.length(); i++) {
  while (res.length() > 0 && res.back() < s[i] && k > 0) {
      res.pop_back();
      k--;
    }
    res.push_back(s[i]);
  }
  while (res.length() > 0 && k > 0) {
    res.pop_back();
    k--;
  }
  return res;
}

//smallest
/*    string str;
    for (auto c : s) {
      while (k > 0 && !str.empty() && c < str.back()) {
        str.pop_back();
        k--;
      }
      str += c;
    }*/

//cp algorithm -> String Hashing  [use 31 for all lowcase , if mixed use 53]
const ll hash[N];
long long compute_hash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
//        inv[i] = mod_power(p_pow);
//        hash[i] = (hash[i] + (c - 'a' + 1) * p_pow) % m; 
    }
    return hash_value;
}
//p>= character size set and next prime
long long compute_hash2(string const& s) {
    const int p = 31;
    const int m2 = 998244353;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m2;
        p_pow = (p_pow * p) % m2;
//        inv[i] = mod_power(p_pow);
//        hash[i] = (hash[i] + (c - 'a' + 1) * p_pow) % m2; 
    }
    return hash_value;
}
//use both hash and hash2 and compare, to reduce collision (1/m * 1/m2) probability of cllision
//(compute_hash(s)==x , compute_hash2(s)==y) both equal for two diff -> same string

//prefix hash -> substring
//(hash[r] - hash[l-1] ) * inv[l]

  vector<int> rabin_karp(string const& s, string const& t) {
    const int p = 31; 
    const int m = 1e9 + 9;
    int S = s.size(), T = t.size();

    vector<long long> p_pow(max(S, T)); 
    p_pow[0] = 1; 
    for (int i = 1; i < (int)p_pow.size(); i++) 
        p_pow[i] = (p_pow[i-1] * p) % m;

    vector<long long> h(T + 1, 0); 
    for (int i = 0; i < T; i++)
        h[i+1] = (h[i] + (t[i] - 'a' + 1) * p_pow[i]) % m; 
    long long h_s = 0;
    for (int i = 0; i < S; i++)
        h_s = (h_s + (s[i] - 'a' + 1) * p_pow[i]) % m; 

    vector<int> occurrences;
    for (int i = 0; i + S - 1 < T; i++) {
        long long cur_h = (h[i+S] + m - h[i]) % m;
        if (cur_h == h_s * p_pow[i] % m)
            occurrences.push_back(i);
    }
    return occurrences;
}

/*Returns true if s1 is subsequence of s2*/
bool issubsequence(string& s1, string& s2){
    int n = s1.length(), m = s2.length();
    int i = 0, j = 0;
    while (i < n && j < m) {
        if (s1[i] == s2[j])
            i++;
        j++;
    }
    return i == n;
}

//int count_unique_substrings(string const& s) {
//longest sum contiguous subarray (kadens algorithm)
ll kadens(vector<ll>&vec,ll start,ll end){
    ll mx = INT_MIN,cs=0;
    for(int i=start;i<=end;i++)
    {
        cs += vec[i];
        if (cs > mx) mx = cs;   //start = s;  end = i;
        if (cs < 0)  cs = 0;    // s = i + 1;
    }
    return mx;
}
//smallest subarray sum
int smallestSumSubarry_sum(int arr[], int n){
    int min_ending_here = INT_MAX;
    int min_so_far = INT_MAX;
    for (int i=0; i<n; i++){
        if (min_ending_here > 0)
            min_ending_here = arr[i];
        else
           min_ending_here += arr[i];
       min_so_far = min(min_so_far, min_ending_here); 
    }
    return min_so_far;
}
//check if the string is palindrome or not
bool isPalindrome(string S){
    string P = S;reverse(P.begin(),P.end());
    if (S == P) return true;
    else return false;
}
bool isPalindrome(vector<ll>v){
    for(int i=0;i<v.size()/2;i++){
        if(v[i]!=v[v.size()-1-i]){
            return false;
        }
    }
    return true;
}

bool check_bracket_sequence(string &s, int i, int j) {
  int sum = 0;
  for(int k = i; k <=j; ++k) {
    if(s[k]=='(') sum += 1;
    else sum += -1;
    if(sum < 0) {
      return false;
      break;
    }
  }
  return (sum==0);
}

// don't forget to add s1 $ s2
vector<int> z_function(string s) {
  int n = s.size();
  vector<int> z(n);
  int l = 0, r = 0;
  for(int i = 1; i < n; i++) {
      if(i < r) {
          z[i] = min(r - i, z[i - l]);
      }
      while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
          z[i]++;
      }
      if(i + z[i] > r) {
          l = i;
          r = i + z[i];
      }
  }
  return z;
}
/*----------------------------------------------precomputation----------------------------------------------------------------------------------------------*/

int table[1000000][25];
void buildSparseTable(int arr[], int n) { 
  for (int i = 0; i < n; i++) 
    table[i][0] = arr[i]; 

  for (int j = 1; j <= log2(n); j++) 
    for (int i = 0; i <= n - (1 << j); i++) 
      table[i][j] = __gcd(table[i][j - 1], 
        table[i + (1 << (j - 1))][j - 1]); 
} 
int query(int L, int R) { 
  int j = (int)log2(R - L + 1); 
  return __gcd(table[L][j], table[R - (1 << j) + 1][j]); 
} 

//prefix sum array - > suffix sum ----> reverse( refixSum , prefixSum+n );
void fillPrefixSum(int arr[], int n, int prefixSum[])
{
    prefixSum[0] = arr[0];
   for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];
}
//main function - >   int arr[n]; for loop  ;  cin >> arr[i];   int prefixSum[n]; fillPrefixSum(arr, n, prefixSum);



/*------------------------------------------------------------------------------------------------------------------------------------------*/

//memset(grid,-1,sizeof(grid));  dp.resize(n+1,-1);
// min/max element index it = find(all(v),*max_element(all(v)))-v.begin();
//element present or not   bool exists = find(all(v),-1) != v.end();
int solve(vector<ll>&v)
{
    int i=0,j=v.size()-1;
    int ans=1;
    while(i<j)
    {
        if(v[i]!=v[j])
        {
            ans=0;
            break;
        }
        i++;
        j--;
    }
    return ans;
}
/*-----------------------------------------------Comparator-----------------------------------------------------------------------------------------*/

//compare -> must return false -> use < or > [don't use <=>]
bool cmp(pair<string,int>&a,pair<string,int>&b){
    if(a.second==b.second){
        return a.first>b.first;
    }
    return a.second<b.second;
}

//compare oparator
bool cmp(pair<ll,ll>&a,pair<ll,ll>&b)
{
    return (a.second<b.second);
}

//lambda
//sort(all(v), [&](int i, int j){return v[i]<v[j];})
auto sortbylen = [&](int a, int b){return a+b;};
auto sum = [&](const auto &a, const auto &b){return a.size()<b.size();};



/*-----------------------------------------------interactive-----------------------------------------------------------------------------------------*/

/*auto query = [&](int i, int j) {
  // input taking format
  cout << "? " << i << " " << j << endl; 
  cout << flush;
  // take query response
  int q;  
  cin >> q;
  return q;
};
int a = query(1, 1);
int b = query(n, 1);
int c = query(n, m);
int num = a + b - (n - 1);
if (num % 2 == 0) {
  int j = 1 + num / 2;
  if (j >= 1 && j <= m) {
    int i = (a + 2) - j;
    if (query(i, j) == 0) {
      cout << "! " << i << " " << j << endl;
      cout << flush;
      // mandatory or do cout.flush() << ....
     // btw still works as endl autometically clears the buffer
      // remove #define endl '
'
      continue;
    }
  }
}
int i = n - (b + c - (m - 1)) / 2;
int j = b + 1 - (n - i);
// print format as written
cout << "! " << i << " " << j << endl;
fflush(stdout); */

/*------------------------------------------------------------------------------------------------------------------------------------------*/


//prime factors store in map
/*map <int,int> a;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            for (int j = 2; j * j <= x; j++) {
                while (x % j == 0) {
                    x /= j;
                    a[j]++;
                }
            }
           if (x != 1) {
                a[x]++;
            }
        }
for (pair <int, int> p : a) {
            int num = p.first;
            int cnt = p.second;
            res += cnt / 2;
            rem += cnt % 2;
}/
//precompute prime factors
/*void precompute() {
vector<ll>isPrime(1e6+1,1);
isPrime[0]=isPrime[1]=0;
vector<vector<ll>>v(1e6+1,vector<ll>());
for(ll i=2;i<=1e6;i++){
    if(isPrime[i]){
        for(ll j=2*i;j<=1e6;j+=i){
            v[j].push_back(i);
       }
    }
  }
}*/

/*how to return set
set<ll> digits(int n) {
vector<ll> st;
   while(n) {
   st,insert(n%10);
   n /= 10;
}
   return st;
} 
*/
/*------------------------------------------------------------------------------------------------------------------------------------------*/
//special function
/*auto get = [&] (int l, int r, int d) -> pair<long long, long long> {
  if (l < d) return pre[d][r];
  long long first = pre[d][r].first - pre[d][l - d].first;
  long long second = pre[d][r].second - pre[d][l - d].second;
  return {first, second};
//auto [first, second] = get(s, e, d);
};*/

/*------------------------------------------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------------------------------------------------*/

//check prime or not
bool isPrime(ll n){
    if(n==1)return false;
    if(n==2 || n==3)return true;
    if(n%2==0) return false;
    for(ll i=3;i*i<=n;i+=2)
    if(n % i==0)return false;
    return true;
}
//check prime or not opttimised , efficient way
bool prime_check(ll n){
    if(n==1) return false;
    if(n==2 || n==3) return true;
    if(n%2==0 || n%3==0) return false;
    for(ll i=5;i*i<=n;i+=6){
        if(((n%i)==0)||(n%(i+2)==0)) return false;
    }
    return true;
}

/*------------------------------------------------------------------------------------------------------------------------------------------*/

void seive(ll n){vector<bool>isprime(n+1,true);for(ll i=2;i<=n;++i){if(isprime[i]){cout<<i;for(ll j=i*i;j<=n;j+=i)  isprime[j]=false;}}}
//seive till root nloglong
int n;
vector<bool> is_prime(n+1, true);
is_prime[0] = is_prime[1] = false;
for (int i = 2; i * i <= n; i++) {
    if (is_prime[i]) {
        for (int j = i * i; j <= n; j += i)
            is_prime[j] = false;
    }
}


/*Mark prime or not in a Range
void precompute() {
vector<bool>isprime(1e5+5,true);
for(ll i=2;i<=1e5+5;++i){
  if(isprime[i]){
    for(ll j=i*i;j<=1e5+5;j+=i)  
      isprime[j]=false;
    }
  }
}*/


//storing all divisors in a vector
//use set<ll>st
vector <ll> divisors(ll n){
    vector<ll> v;
    for (ll i=1; i<=(ll)sqrt(n); i++){
        if (n % i == 0){
            v.emplace_back(i);  //st.insert(i)
            if ((n / i) != i) v.emplace_back(n / i);  //st.insert(n / i)
        }
    }
    return v;
}




//storing all prime factors, use set to store unique, don't pass value
vector <ll> findPrimeFactors(ll n){
    vector<ll> primeFactors;
    while (n%2== 0) primeFactors.push_back(2), n = n/2;
    for (ll i = 3; i*i <= n; i = i+2){
        while (n%i == 0){ 
            primeFactors.push_back(i);
            n = n/i;
        }
    }
    if (n > 2) primeFactors.push_back(n); //if(n!=1)v.push_back(n)
    return primeFactors;
}

/*--------------------------------------------Remember----------------------------------------------------------------------------------------------*/
// DSU
void make(int v) {
    parent[v] = v;
    sz[v] = 1;
}

int find(int v) {
    if (parent[v] == v) return v;
    return parent[v] = find(parent[v]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
        if (sz[a] < sz[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        sz[a] += sz[b];
    }
}

// for (int i = 1; i <= n; ++i) {
//     make(i);
// }


//another approach class
class UnionFind
{
private:
    vector<int> par;
    vector<int> sz;

public:
    UnionFind(int n)
    {
        par = vector<int>(n);
        iota(par.begin(), par.end(), 0);
        sz = vector<int>(n, 1);
    }

    int find(int u)
    {
        // this optimisation was good.
        if (par[u] != par[par[u]])
            par[u] = find(par[par[u]]);
        return par[u];
    }

    bool connected(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
            return true;
        return false;
    }

    bool join(int u, int v)
    {
        u = find(u);
        v = find(v);
        if (u == v)
            return false;
        if (sz[u] <= sz[v])
        {
            sz[v] += sz[u];
            par[u] = v;
        }
        else
        {
            sz[u] += sz[v];
            par[v] = u;
        }
        return true;
    }
};
// call UnionFind uf1(n), uf2(n);

/*--------------------------------------------Remember----------------------------------------------------------------------------------------------*/
//check if possible to make the ans in 0(n^2), by manupulation, LLMAX fot high

/*  bool check() {}
// use LLMAX for high or check ehat can be max , otherwise overflow  **while(!check(high)) high*=2;
    auto check = [&](int mid)->bool {
    };
    int low = 0, high = 1e18, ans = -1, loop = 100;
    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (check(mid)) {
        ans = mid;
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

Ternary search, break in 3 segments (logn base 3)

    int low = 0, high = 1e18, ans = -1, loop = 100;
    while (low <= high) {
      int mid1 = low + (high - low) / 3, mid2 = high - (high - low) / 3;
      int res = query(mid1, mid2);
      if (res == mid1 * mid2 / check) {
        low = mid2 + 1;
        high = mid - 1;
      } else if (res == mid1 * (mid2 + 1)){
        ans = mid2;
        low = mid1 + 1;
        high = mid2 - 1;
      } else {
        ans = mid1;
        high = mid1 - 1;
      }
    }*/


//cp algorithm code, once r - l < 3 stop, it's not possible to to chose mid1, mid2
/*double ternary_search(double l, double r) {
    double eps = 1e-9;              //set the error limit here
    while (r - l > eps) {   // r - l >= 3 will work or r - l > 3
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = f(m1);      //evaluates the function at m1
        double f2 = f(m2);      //evaluates the function at m2
        if (f1 < f2)
            l = m1;
        else
            r = m2;
    }
    return f(l);                   //return the maximum of f(x) in [l, r]
}*/
//if x is increasing at top and started decreasing for [low to high] range, ternary search helps to find x
//    .
//   .  .
// .      .
//.         .
/*------------------------------------------------------------------------------------------------------------------------------------------*/




// code starts here


int32_t main()
{

    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    clock_t time_req=clock();

    ankan_nayak_1412();
    //calFact()

    ll tt;
    cin >> tt;
    read:
    while (tt--) 
    {



    }
    #ifndef ONLINE_JUDGE
    cout<<"Time : "<<fixed<<setprecision(6)<<((double)(clock()-time_req))/CLOCKS_PER_SEC<<endl;
    #endif

    return 0;
}

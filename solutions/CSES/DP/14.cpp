#include <iostream>
#include <bits/stdc++.h>

using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long



//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>


// Variadic print function for debugging
template<typename... Args>
void print(Args... args) {
    ((cout << args << " "), ...);
    cout << endl;
}

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x: v) in >> x;
    return in;
}

// Overload for vector
template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

// Overload for set
template<typename T = int>
ostream &operator<<(ostream &out, const set<T> &s) {
    for (const T &x : s) out << x << ' ';
    return out;
}

// Overload for map
template<typename K = int, typename V = int>
ostream &operator<<(ostream &out, const map<K, V> &m) { 
    for (const auto &[key, value] : m) out << '(' << key << ": " << value << ") ";
    return out;
}

// Overload for pair
template<typename A = int, typename B = int>
ostream &operator<<(ostream &out, const pair<A, B> &p) {
    return out << p.first << ", " << p.second;
}



void kemo() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    #ifndef ONLINE_JUDGE
        freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    #endif
}



void solve(int test_case);

signed main() {
    kemo();
 
    int t = 1;
  //  cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}







const int mod = 1000000007;

int add(int a, int b) {
    return ((a % mod) + (b % mod)) % mod;
}

int mul(int a, int b) {
    return ((a % mod) * (b % mod)) % mod;
}

int fast_power(int a,int b){
    int res=1;
    while(b){
        if(b&1) res = mul(a,res);
        a =mul(a,a);
        b/=2;
    }

    return res;
}

int modinv(int x , int m){
	return fast_power(x,m-2);
}

int divison(int a,int b){
    return mul( a , fast_power(b,mod-2));
}
int sub(int a, int b) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

void solve(int test_case) {
    
   int n; cin>>n;
   int sum = n*(n+1)/2;
   if(sum&1) return void(cout<<0);
   vi dp(sum/2+1);
   dp[0] = 1;
   for(int i = 1 ; i <= n ; i++){
        for(int j = sum/2 ; j >= 1 ; j--){
            if(j - i >= 0){
                (dp[j]+=dp[j-i])%=mod;
            }
        }
   }

   
   cout<<divison(dp[sum/2],2)<<"\n";
}

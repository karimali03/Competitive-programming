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

void solve(int test_case);

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
  
   
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

const int mod = 998244353;
void solve(int test_case){
    int n,m,k; cin>>n>>m>>k;
    vii dp(n+5,vi(m+5));
    f(i,1,m+1) dp[0][i] = 1;
    for(int i = 1 ; i  < n ; i++){
        for(int j = 1 ; j <= m ; j++) {
            dp[i-1][j]=( dp[i-1][j]%mod + dp[i-1][j-1]%mod)%mod;
        }
        int al = dp[i-1][m];
        for(int x = 1 ; x <= m ; x++){
           if(k) // if k = 0   l = x , r = x-1 so we need to avoid it
           dp[i][x] = ( al%mod - dp[i-1][min(x+k-1,m)]%mod 
           + dp[i-1][max(x-k,0ll)]%mod + mod )%mod;
          else dp[i][x] = al;
        }
    }
    
    int sum = 0;
    for(int i = 1 ; i <= m ; i++) sum = (sum%mod + dp[n-1][i]%mod)%mod;
    cout<<sum<<ln;
}
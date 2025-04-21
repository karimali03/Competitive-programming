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
#define cout(v,n) for(int i = 0 ; i < n && cout<<v[i]<<" "; i++);
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long

//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
//using namespace __gnu_pbds;
//#define ordered_set tree<ll, null_type,less<ll>, rb_tree_tag,tree_order_statistics_node_update>

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

const int mod = 1e9+7;
void solve(int test_case){
    int n,k; cin>>n>>k;
    vi v(n); cin>>v;
    vii dp(n+1,vi(100005));

    for(int i = 0 ;  i <= min(k,v[0]) ; i++) dp[1][i] = 1;


    for(int i = 2 ; i <= n ; i++){
        for(int x = 1 ; x <= k ; x++){
            dp[i-1][x] = (dp[i-1][x]%mod + dp[i-1][x-1]%mod)%mod;
        }
        for(int cur = 0 ; cur <= k ; cur++){
            dp[i][cur] = dp[i-1][cur];
            if(cur-v[i-1] > 0) 
            dp[i][cur] = (dp[i][cur]%mod + mod - dp[i][cur-v[i-1]-1]%mod)%mod;
        }

    }

    cout<<dp[n][k]<<ln;
}
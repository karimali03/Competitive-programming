#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}


const int MOD = 998244353;
void solve(int test_case) {
    int n,k; cin>>n>>k;
    n = min(n , k+1);
    vii dp(n,vi(k+1));
    for(int i = 1 ; i <= k ; i++) dp[0][i] = 1;
    for(int i = 1 ; i < n ; i++){
        vi pre(k+1);
        for(int x = 1 ; x <= k ; x++){
            (pre[x] = pre[x-1] + dp[i-1][x])%=MOD;
        } 
        for(int avg = 1 ; avg <= k ; avg++){
            int ns = avg * (i+1);
            int l = max( 1ll , ( ns - k + i - 1) / i);
            int r = min ( k , ( ns -  1 ) / i);
            if(l<=r){
                dp[i][avg] += pre[r] - pre[l-1];
                dp[i][avg] += MOD;
                dp[i][avg] %= MOD;
            }
       }
    }
    int res= 0;
    for(int x = 1 ; x <= k ; x++){
            (res += dp[n-1][x])%=MOD;
    }
    cout<<res<<" ";
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}
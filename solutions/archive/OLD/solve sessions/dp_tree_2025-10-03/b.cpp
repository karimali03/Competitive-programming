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

void solve(int test_case) {
    int n,MOD; cin>>n>>MOD;
    vii g(n);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    vi dp(n,1);
    function<void(int,int)> rec = [&](int u,int p){
        for(auto v : g[u]){
            if(v == p) continue;
            rec(v,u);
            (dp[u]*=(1+dp[v]))%=MOD;
        }
    };
    rec(0,-1);
    vi ans(n);
    function<void(int,int)> reroot = [&](int u,int p){
        ans[u] = dp[u];
        int sz = g[u].size();
        vi pre(sz+1,1),suf(sz+2,1);
        for(int i = 0 ; i < sz ; i++){
            pre[i+1] = ( pre[i] * (1+dp[g[u][i]]) ) % MOD;
        }
        for(int i = sz-1 ; i >= 0 ; i--){
            suf[i+1] = ( suf[i+2] * (1+dp[g[u][i]]) )%MOD;
        }
        for(int i = 0 ; i < sz ; i++){
            int v = g[u][i];
            if(v == p) continue;
            // make v the root
            int og = dp[u];
            dp[u] = ( pre[i] * suf[i+2] ) % MOD;
            dp[v] = ( dp[v] * (1 + dp[u]) ) % MOD;
            reroot(v,u);
            // return u the root
            dp[u] = og;
        }
    };
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}
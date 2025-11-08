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
    int n,k; cin>>n>>k;
    vii g(n);
    for(int i = 1 ; i < n ;i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vi sz(n);
    vi dp(n);
    function<void(int,int)> dfs = [&](int x,int p){
        sz[x] = 1;
        for(auto it : g[x]) if(it != p){
            dfs(it,x);
            sz[x] += sz[it];
            dp[x] += dp[it];
        }
        dp[x] += (sz[x] >= k);
    };
    dfs(0,-1);
    int ans = 0;
    function<void(int,int)> reroot = [&](int x,int p){
        ans += dp[x];
     //   cout<<x<<" "<<dp[x]<<" "<<sz[x]<<ln;
        for(auto it : g[x]) if(it != p){
            int ogsz = sz[x];
            int og = dp[x];
            dp[x] -= (sz[x] >= k) + dp[it];
            dp[it] -= (sz[it] >= k);
            sz[x] -= sz[it];
            sz[it] += sz[x];
            dp[x] += (sz[x] >= k);
            dp[it] += dp[x] + (sz[it] >= k);
            reroot(it,x);
            dp[x] = og  , sz[x] = ogsz;
        }
    };
    reroot(0,-1);
    cout<<ans<<ln;
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
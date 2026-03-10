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

const int MOD = 1e9+7;
void solve(int test_case) {
    int n; cin>>n;
    n++;
    vii g(n);
    g[0].push_back(1);
    for(int i = 1;i < n ; i++){
        int l,r; cin>>l>>r; 
        if(l == 0 && l == r) continue;
        g[i].push_back(l); g[i].push_back(r);
    }
    vi dp(n);
    int timer = -1;
    vi in(n);
    vi res(n+5);
    function<void(int)> dfs = [&](int x){
     //   cout<<x<<endl;
        int sum = 0;
        in[x] = ++timer;
        for(auto &it : g[x]){
            dfs(it);
            (sum += dp[it])%=MOD;
        }
        (dp[x] = 1 + g[x].size() + sum)%=MOD;
     //   cout<<" "<<dp[x]<<ln;
        (res[in[x]] += dp[x])%=MOD;
        res[timer+1] = (res[timer+1] - dp[x] + MOD)%MOD;
    };
    dfs(1);
    f(i,1,n+2) (res[i] += res[i-1])%=MOD;
    for(int i = 1 ; i < n ; i++) cout<<res[in[i]]<<" ";
    cout<<ln;
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
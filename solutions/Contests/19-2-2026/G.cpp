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

const int INF = 1e15;
void solve(int test_case) {
    int n,q; cin>>n>>q;
    n++;
    vi dp(n);
    vii g(n);
    g[0].push_back(1);
    for(int i = 1 ;i  < n; i++){
        int l,r; cin>>l>>r;
        if(l == 0 && l == r) continue;
        g[i].push_back(l); g[i].push_back(r);
    }
    vi tour;
    vi in(n);
    vii up(20,vi(n)),cost(20,vi(n,INF));
    function<void(int,int)> dfs = [&](int x,int p){
        in[x] = tour.size();
        tour.push_back(x);
        up[0][x] = p; 
        for(int j = 1 ; j < 20 ; j++){
            up[j][x] = up[j-1][up[j-1][x]];
        }
        int sum = 0;
        for(auto &it : g[x]){
            dfs(it,x);
            sum += dp[it];
            tour.push_back(x);
        }
        dp[x] = 1 + sum + (int)g[x].size();
    };
    dfs(0,0);
    for(int i = 0; i < n ; i++){
        if(i) cost[0][i] = dp[i];
        else cost[0][i] = INF;
    }
    for(int j = 1 ; j < 20 ; j++){
        for(int i = 0;i < n ; i++){
            cost[j][i] = min( INF , cost[j-1][i] + cost[j-1][up[j-1][i]]);
        }
    }
    auto get = [&](int x,int k){
        for(int j = 19 ; j >= 0 ; j--){
            if(cost[j][x] <= k){
                k -= cost[j][x];
                x = up[j][x];
            }
        }
        if(x == 0) return 0ll;
        return tour[in[x]+k];
    };
    while(q--){
        int x,k; cin>>x>>k;
        int ans = get(x,k);
        cout<<ans<<" ";
    }
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
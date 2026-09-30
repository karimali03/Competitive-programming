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


const int M = 1e9+7;

const int N = 200005;
int dp[N][2]{};

struct dsu {
    vector<int> size, par;
    int cc;

    dsu(int n) :size(n, 1), par(n),cc(n) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        return par[x] = get(par[x]);
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        return true;
    }

};

void solve(int test_case) {
    int n; cin>>n;
    vi v(n); cin>>v;
    vi pre(n+1);
    auto add = [&](int l,int r){
        if(l > r) return; 
        l = max(l , 0ll);
        r = min(r , n-1);
        pre[l]++; pre[r+1]--;
    };
    for(int i = 0;i < n ; i++){
        if(v[i] == -1) continue;
        add(i-v[i]+1,i+v[i]-1);
    }
    for(int i = 1 ; i < n ; i++) pre[i] += pre[i-1];
    auto can = [&](int x){
        return x >=0 && x<n && (pre[x]==0);
    };
    vector<pair<int,int>>edg;
    int res = 1;
    vi fixed(n);
    for(int i = 0 ;i < n ; i++){
        if(v[i]==-1) continue;
        int l = i + v[i];
        int r = i - v[i];
        auto L = can(l) , R = can(r);
        if(!L && !R){
            cout<<0<<ln; return;
        }
        if(l == r){
            fixed[l] = 1;
        }else if(L && R){
            edg.push_back({l,r});
        }else{
            fixed[L ? l : r] = 1;
        }
    }
    
    vi vis(n);
    vii g(n);
    for(auto &[a,b] : edg){
        if(fixed[a] || fixed[b]) continue;
        g[a].push_back(b); g[b].push_back(a);
    }
    int cc = 0;
    function<void(int)> dfs = [&](int x){
        cc++;
        vis[x] = 1;
        for(auto &it : g[x]) if(!vis[it]) dfs(it);
    };
    for(int i = 0;i < n ; i++){
        if(fixed[i] || vis[i]) continue;
        if(g[i].empty()) continue;
        cc = 0;
        dfs(i);
        if(cc > 1){
            ll cur = dp[cc-1][1] + dp[cc-1][0];
            cur %= M;
            res *= cur; res %= M;
        }
    }
    for(int i = 0;i < n ; i++){
        if(vis[i] || fixed[i]) continue;
        if(!can(i)) continue;
        res <<=1; res %= M;
    }
    if(count(all(v),-1) == n){
        res = (res - 1 + M)%M;
    }
    cout<<res<<ln;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    dp[0][1] = dp[0][0] = 1;
    for(int i = 1 ; i < N ; i++){
        // x == 0 
        dp[i][0] += dp[i-1][1];
        dp[i][0] %= M;
        // x = 1
        dp[i][1] += dp[i-1][0];
        dp[i][1] %= M;
        dp[i][1] += dp[i-1][1];
        dp[i][1] %= M;
    }
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}
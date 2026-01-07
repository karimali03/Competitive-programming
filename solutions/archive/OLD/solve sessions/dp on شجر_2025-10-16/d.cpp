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
    int n;cin>>n;
    vec<vec<pair<int,int>>> g(n);
    vec<pair<int,int>>edges(n-1);
    for(int i=0;i<n-1;i++){
        int x,y; cin>>x>>y; x--,y--;
        edges[i] = {x,y};
        g[x].push_back({y,i}); g[y].push_back({x,i});
    }
    vii dp(n,vi(2,-1));
    function<int(int,int,int)> rec = [&](int x,int p,int ch) -> int{
        int &ret = dp[x][ch];
        if(~ret) return ret;
        vi low,high;
        int sz = 0;
        ret = 1e16;
        for(auto [it,idx] : g[x]) if(it != p){
            low.push_back(rec(it,x,0));
            high.push_back(rec(it,x,1));
            sz++;
        }
        if(sz){
            vi ac(sz);
            int sum = 0;
            for(int i=0;i<sz; i++) ac[i] = high[i] - low[i] , sum +=low[i];
            sort(all(ac));
            int pt = 0;
            for(int deg = 0 ; deg <= min(2-ch,sz); deg++){
                int cur = (sz - deg) + sum;
                ret = min(ret , cur);
                sum += ac[pt++];
            }
        }
        else ret = 0;
        return ret;
    };
    vi del(n);
    function<void(int,int,int)> build = [&](int x,int p,int ch){
        int opt = rec(x,p,ch);
        vi low,high,id;
        int sz = 0;
        for(auto [it,idx] : g[x]) if(it != p){
            low.push_back(rec(it,x,0));
            high.push_back(rec(it,x,1));
            id.push_back(idx);
            sz++;
        }
        if(sz){
            vec<pair<int,int>> ac(sz);
            int sum = 0;
            for(int i=0;i<sz; i++){
                ac[i] = { high[i] - low[i] , id[i]};
                sum +=low[i];
            } 
            sort(all(ac));
            int pt = 0;
            for(int i = 0;i < sz ; i++) del[ac[i].second] = 1;
            for(int deg = 0 ; deg <= min(2-ch,sz); deg++){
                int cur = (sz - deg) + sum;
                if(cur == opt){
                    for(auto [it,idx] : g[x]) if(it != p){
                        if(del[idx]) build(it,x,0);
                        else build(it,x,1);
                    }
                    return;
                }
                del[ac[pt].second] = 0;
                sum += ac[pt++].first;
            }
        }
    };
    build(0,-1,0);
    vi vis(n);
    vi edg;
    function<void(int,int)> dfs = [&](int x,int p){
        vis[x] = 1;
        int sz = 0;
        for(auto [it,idx] : g[x]) if(it != p && !del[idx]) sz++;
        if(sz == 2) edg.clear();
        else if(sz == 0) edg.push_back(x);
        for(auto [it,idx] : g[x]) if(it != p && !del[idx]) dfs(it,x);
    };
    vii res;
    for(int i = 0 ;i  < n;  i++){
        if(!vis[i]){
            edg.push_back(i);
            dfs(i,-1);
            res.push_back(edg);
            edg.clear();
        }
    }
    int ans = rec(0,-1,0);
    cout<<ans<<ln;
    vii op(ans,vi(4));
    int cur = 0;
    for(int i = 0 ; i < n-1 ; i++){
        if(del[i]){
            op[cur][0] = edges[i].first;
            op[cur][1] = edges[i].second;
            cur++;
        }
    }

    int leaf = res[0][0];
    for(int i = 1 ; i < (int)res.size() ; i++){
        op[i-1][2] = leaf;
        op[i-1][3] = res[i][0];
        leaf = res[i].back();
    }
    for(auto &it : op){
        for(auto &x : it) cout<<x+1<<" ";
        cout<<ln;
    }
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
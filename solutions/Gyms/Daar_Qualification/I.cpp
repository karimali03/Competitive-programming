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
    vi v(n); cin>>v;
    vii g(n);
    vector<pair<int,int>>edg;
    for(int i = 1 ; i < n ; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
        edg.push_back({x,y});
    }
    vi in(n),out(n),lvl(n);
    int timer = -1;
    auto is_ansc = [&](int x,int y){
        return in[x] <= in[y] && out[y] <= out[x];
    };
    vi xr(n);
    function<void(int,int)> rec = [&](int x,int p){
        xr[x] = v[x];
        lvl[x] = p == -1 ? 0 : lvl[p] + 1;
        in[x] = ++timer;
        for(auto &it : g[x]) if(it != p){
            rec(it,x);
            xr[x] ^= xr[it];
        }
        out[x] = ++timer;
    };
    rec(0,-1);
    for(int i = 0;i < n-1;i++){
        auto [x,y] = edg[i];
        if(lvl[x] < lvl[y]) edg[i] = {y,x};
    }
  
    if(k == 1){
        cout<<xr[0]<<ln;
    }else if(k == 2){
        int res = 0;
        for(int i = 0 ; i < n-1 ; i++){
            auto [x,y] = edg[i];
            res = max(res , xr[x] + (xr[0]^xr[x]) );
        }
        cout<<res<<ln;
    }else if(k == 3){
        int res = 0;
        int opt[3],val[3];
        for(int i = 0;i < n-1 ; i++){
            for(int j = i+1 ;j < n-1 ; j++){
                auto [a,b] = edg[i];
                auto [c,d] = edg[j];
                opt[0] = 0 , opt[1] = a , opt[2] = c;
                sort(opt,opt+3,[&](int x,int y){
                    return lvl[x] < lvl[y];
                });
                int cur = 0;
                f(x,0,3) val[x] = xr[opt[x]];
                for(int x = 2; x > 0; x--){
                    for(int y = x - 1; y >= 0; y--){
                        if(is_ansc(opt[y], opt[x])) {
                            val[y] ^= val[x];
                        }
                    }
                }
                f(x,0,3) cur += val[x];
                res = max(res, cur);
            }
        }
        cout<<res<<ln;
    }else{
        int res = 0;
        int opt[4],val[4];
        for(int i = 0;i < n-1 ; i++){
            for(int j = i+1 ;j < n-1; j++){
                for(int k = j+1 ; k < n-1 ; k++){
                    auto [a,b] = edg[i];
                    auto [c,d] = edg[j];
                    auto [e,f] = edg[k];
                    opt[0]=0,opt[1]=a,opt[2]=c,opt[3]=e;
                    sort(opt,opt+4,[&](int x,int y){
                        return lvl[x] < lvl[y];
                    });
                    int cur = 0;
                    f(x,0,4) val[x] = xr[opt[x]];
                    for(int x = 3; x > 0; x--){
                        for(int y = x - 1; y >= 0; y--){
                            if(is_ansc(opt[y], opt[x])) {
                                val[y] ^= val[x];
                            }
                        }
                    }
                    f(x,0,4) cur += val[x];
                    res = max(res, cur);
                }
            }
        }
        cout<<res<<ln;
    }

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
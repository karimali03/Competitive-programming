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



struct HLD {
    
    vi big,sz,depth,head,in,par;
    vii g;
    void init(int x,int d){
        sz[x] = 1;
        big[x] = -1;
        depth[x] = d;
        for(auto &it : g[x]){
            if(it == par[x]) continue;
            par[it] = x;
            init(it,d+1);
            sz[x] += sz[it];
            if(big[x] == -1 || sz[it] > sz[big[x]]) big[x] = it;
        }
    };
    
    void flatten(int x,int &timer){
        in[x] = ++timer;
        if(~big[x]){
            head[big[x]] = head[x];
            flatten(big[x],timer);
        } 
        for(auto &it : g[x]){
            if(par[x] == it || it == big[x]) continue;
            head[it] = it;
            flatten(it,timer);
        }
    }
    HLD(int n,vii &g):g(g){
        big = sz = depth = in = par = head = vi(n);
        init(0,0);
        head[0] = 0;
        int timer = -1;
        flatten(0,timer);
    };
    
    
    vector<pair<int,int>> query(int x,int y){
        vector<pair<int,int>> ret;
        while(true){
            if(depth[x] > depth[y]) swap(x,y);
            if(head[x] == head[y]){
                ret.push_back({in[x],in[y]});
                return ret;
            }
            if(depth[head[x]] < depth[head[y]]) swap(x,y);
            // x will not exceed lca
            // y may exceed lca
            ret.push_back({in[head[x]] , in[x]});
            x = par[head[x]];
        }
        return ret;
    }
    
    
};

void solve(int test_case) {
    int n,q; cin>>n>>q;
    vii g(n);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    HLD hld(n,g);

    while(q--){
        int a,b,c,d; cin>>a>>b>>c>>d; a--,b--,c--,d--;
        auto r1 = hld.query(a,b);
        auto r2 = hld.query(c,d);
        // sort(all(r1));
        // sort(all(r2));
        int res = 0;
        for(int i = 0;i < (int)r1.size() ; i++){
            for(int j = 0; j < (int)r2.size() ; j++){
                int l = max(r1[i].first , r2[j].first);
                int r = min(r1[i].second , r2[j].second);
                if(l <= r) res += (r-l+1);
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
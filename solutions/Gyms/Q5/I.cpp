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


struct DSU {
    // dif: Relation of node 'i' to 'par[i]'  
    //  Logic: Value[i] - Value[par[i]] = dif[i]
    vector<int> sz, par, dif;
    vector<array<int,8>>hist;
    int cc; 
    DSU(){}
    DSU(int n) : sz(n, 1), par(n), dif(n, 0), cc(n) {
        for (int i = 0; i < n; i++) par[i] = i;
        hist.reserve(n);
    }

    int get(int x) {
        while(x != par[x]){
            x = par[x];
        }
        return x;
    }

    bool merge(int x, int y, int w) {
        // We are given relation: Value[x] - Value[y] = w
        int rx = get(x), ry = get(y);
        array<int,8> cur = {-1,-1,-1,-1,-1,-1,-1,-1};
        hist.push_back(cur);
        // Case 1: Already in same set
        if (rx == ry) {
            // Check consistency. Derived relation must match given 'w'.
            // Logic: (x->root) - (y->root) == (x->y)
            return (dif[x] - dif[y] == w);
        }

        // Case 2: Different sets (Triangle Logic)
        // We need to connect root_x (rx) to root_y (ry).
        // Formula: Path(rx->ry) = Path(rx->x) + Path(x->y) + Path(y->ry)
        int cost = dif[y] - dif[x] + w;
        // x y rx ry dif[rx] dif[ry] sz[rx] sz[ry]
        if (sz[x] > sz[y]) {
            par[ry] = rx;
            dif[ry] = -cost; 
            sz[rx] += sz[ry];
        } else {
            par[rx] = ry;
            dif[rx] = cost;
            sz[ry] += sz[rx];
        }
        hist.back() = {x,y,rx,ry,dif[rx],dif[ry],sz[rx],sz[ry]};
        cc--;
        return true;
    }

    void rollback(int state){
        while((int)hist.size() > state){
            auto [x,y,rx,ry,dx,dy,sx,sy] = hist.back(); hist.pop_back();
            if(x == -1) continue;
            if(sx > sy){
                par[ry] = ry;
                dif[ry] = dy;
                sz[rx] -= sz[ry];
            }else{
                par[rx] = rx;
                dif[rx] = dx;
                sz[ry] -= sz[rx];
            }
            cc++;
        }
    }

    int state(){
        return hist.size();
    }
};

struct SegTree {
    int n;
    vector<vector<array<int,3>>> t; // Tree array
    
    // NEUTRAL VALUE  
    const vector<array<int,3>> VAL_NEUTRAL = {}; // Neutral for tree values (e.g., -2e18 for Max, 0 for Sum)
    DSU ds;
  
    SegTree(int n,int dsu_n) : n(n){
        t.assign(2 * n, VAL_NEUTRAL); 
        ds = DSU(dsu_n);
    }
 
    void apply(int p,array<int,3>& tag) {
        t[p].push_back(tag);
    }

    void update(int l, int r,array<int,3>tag) {
        r++; // Adjust for inclusive range
        l += n; r += n;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, tag);
            if (r & 1) apply(--r, tag);
        }
    }


    void dfs(int u,bool vld){
        int state = ds.state();

        for(auto [x,y,c] : t[u]){
            if(!ds.merge(x,y,c)) vld = false;
        }
        // leaf
        if(u >= n){
            t[u].push_back({vld,0,0});
        }else{
            dfs(u << 1,vld); // left
            dfs(u << 1 | 1,vld); // right
        }

        ds.rollback(state);
    }
};


void solve() {
    int n,q; cin>>n>>q;
    SegTree sg(q,n);
    map<array<int,3>,int>mp;
    for(int i = 0 ;i < q ; i++){
        char ch; cin>>ch;
        if(ch == '+'){
            int x,y,c; cin>>x>>y>>c; x--,y--;
            mp[{x,y,c}] = i;
        }else if(ch == '-'){
            int x,y,c; cin>>x>>y>>c; x--,y--;
            int start = mp[{x,y,c}];
            sg.update(start,i-1,{x,y,c});
            mp.erase({x,y,c});
        }
    }
    for(auto &[a,b] : mp){
        sg.update(b,q-1,a);
    }
    sg.dfs(1,true);
    for(int i = 0; i < q ; i++){
        if(sg.t[i+q].back()[0]) YES;
        else NO;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    for (int i = 1; i <= t; i++) {
        solve();
    }

    return 0;
}

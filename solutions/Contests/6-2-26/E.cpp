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


struct TwoECC {
    vector<vector<int>> g;
    vector<int> low, tin, org;
    vector<pair<int,int>> bridges;
    stack<int> st;
    vector<vector<int>> TwoEdgeCC, tree;
    int timer, n;

    TwoECC(vector<vector<int>> &adj) : g(adj) {
        timer = 0;
        n = g.size();
        low = tin = org = vector<int>(n, -1);
        
        for(int i = 0; i < n; i++) {
            if(tin[i] == -1) dfs(i, -1);
        }

        // Build the Tree
        tree = vector<vector<int>>(n);
        for(int i = 0; i < n; i++) {
            for(auto &it : g[i]) {
                if(org[i] != org[it]) {
                    tree[org[i]].push_back(org[it]);
                }
            }
        }
    }

    void dfs(int v, int p) { 
        low[v] = tin[v] = timer++;
        st.push(v);
        bool skip_p = false; 
        for(auto u : g[v]) { 
            if(u == p && !skip_p) {
                skip_p = true;
                continue;
            }
            
            if(tin[u] != -1) { // back edge 
                low[v] = min(low[v], tin[u]);
            } else { // tree edge
                dfs(u, v); 
                low[v] = min(low[v], low[u]);
                if(low[u] > tin[v]) bridges.push_back({v, u});
            }
        }

        if(low[v] == tin[v]) {
            vector<int> comp;
            while(true) {
                int node = st.top();
                st.pop();
                comp.push_back(node);
                if(node == v) break;
            }
            
            int r = comp[0]; 
            for(auto &it : comp) org[it] = r;
            TwoEdgeCC.push_back(comp);
        }
    }
};

struct LCA{
    int LOG,n;
    vii g,up;
    vi lvl,vis;
    LCA(vii &g) :g(g){
        n = g.size();
        LOG = __lg(n) + 1;
        up = vii(n,vi(LOG));
        lvl = vis = vi(n);
        // forests
        for(int i = 0;i < n ; i++) if(!vis[i]) dfs(i,i);
    };

    void dfs(int u,int p){
        vis[u] = 1;
        up[u][0] = p;
        lvl[u] = (u == p ? 0 : lvl[p] + 1);

        for(int i = 1 ;i < LOG ; i++){
            up[u][i] = up[up[u][i-1]][i-1];
        }

        for(auto v : g[u]) if(v != p){
            if(!vis[v]) // multiedges
            dfs(v,u);
        }
    }


    int get_root(int u){
        return get_kth(u,lvl[u]);
    }

    int get_kth(int u,int k){
        for(int i = 0;i < LOG ; i++){
            if((k>>i)&1) u = up[u][i];
        }
        return u;
    }

    int lca(int u,int v){
        if(lvl[u] > lvl[v]) swap(u,v);
        v = get_kth(v,lvl[v]-lvl[u]);
        if(u == v) return u;
        for(int i = LOG-1 ; i >= 0 ; i--){
            if(up[v][i] != up[u][i]){
                v = up[v][i];
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    int get_dist(int u,int v){
        int lc = lca(u,v);
        return lvl[u] + lvl[v] - 2 * lvl[lc];
    }
};

void solve(int test_case) {
    int n,m,q; cin>>n>>m>>q;
    vii g(n);
    for(int i = 0 ; i < m; i++){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    TwoECC bt(g);
    LCA st(bt.tree);

    vi up(n),down(n);
    while(q--){
        int l,r; cin>>l>>r; l--,r--;
        l = bt.org[l] , r = bt.org[r];
        if(l == r) continue;
    
        if(st.get_root(l) != st.get_root(r)){
            cout<<"No\n";
            return;
        }
    
        int lc = st.lca(l,r);
        up[lc]--; up[l]++;
        down[lc]--; down[r]++;
    }
   
    vi vis(n);
    function<void(int,int)> calc = [&](int x,int p){
        vis[x] = 1;
        for(auto &it : bt.tree[x]) if(it != p){
            calc(it,x);
            up[x] += up[it];
            down[x] += down[it];
        }
    };
    for(int i = 0; i < n ; i++) if(!vis[bt.org[i]]) calc(bt.org[i],-1);
    for(int i = 0;i < n ; i++){
        if(up[i] && down[i]){
            cout<<"No\n";
            return;
        }
    }
    cout<<"Yes\n";
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
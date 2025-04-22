#include "bits/stdc++.h"
#define ll long long
#define pl pair<ll, ll>
#define vi vector<ll>
#define vp vector<pl>
#define vii vector<vi>
#define all(X) X.begin(), X.end()
#define int ll
using namespace std;

// Heavy Light Decomposition
struct HLD {
    int size, timer;
    vi lvl, par, heavy, head, indeg, sz;
    vii adj;
 
    void dfs(int u, int p) {
        par[u] = p;
        sz[u] = 1;
        for (int v : adj[u]) if (v != p) {
            lvl[v] = lvl[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
            if (!heavy[u] || sz[v] > sz[heavy[u]]) heavy[u] = v;
        }
    }
    
    void decompose(int u, int p){
        indeg[u] = timer++;
        if (heavy[u]) {
            head[heavy[u]] = head[u];
            decompose(heavy[u], u);
        }
        for (int v : adj[u]) if (v != p && v != heavy[u]) {
            head[v] = v;
            decompose(v, u);
        }
    }
 
    HLD(int n, vii &adj) : size(n), lvl(n+1), par(n+1), heavy(n+1), head(n+1), indeg(n+1), adj(adj), sz(n+1) {
        dfs(1, 0);
        timer = 1;
        head[1] = 1;
        decompose(1, 0);
    }
 
    deque<pl> get_path(int u, int v) {
        deque<pl> path;
        bool us = 1;
        while (head[u] != head[v]) {
            if (lvl[head[u]] < lvl[head[v]]) swap(u, v), us^=1;
            // if cost in edges not node let indeg[head[u]] + 1. and edge cost get down to child node.
            if (us) path.push_back({indeg[head[u]], indeg[u]});
            else path.push_back({indeg[u], indeg[head[u]]});
            
            u = par[head[u]];
        }
        if (lvl[u] > lvl[v]) swap(u, v), us^=1;
        // u is lca between u and v
        if (us) path.push_back({indeg[u], indeg[v]});
        else path.push_back({indeg[v], indeg[u]});
        return path;
    }
};

void solve(){
    ll n;

    cin >> n;
    string s; cin >> s;

    vii adj(n + 1);
    for (int i = 0; i < n-1; i++)
    {
        ll u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    HLD hl(n, adj);

    string t;
    t.resize(n+1);
    for (int i = 1; i <= n; i++)
    {
        t[hl.indeg[i]] = s[i-1];
    }
    
    t[0] = 'a';
    ll q; cin >> q;
    while (q--)
    {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;
        auto L = hl.get_path(a, b);
        auto R = hl.get_path(c, d);
    
        cout << comp(hs, hsr, L, R);
    }    
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    
   
    int size;
    size = 1;
    cin >> size;
    while (size--) solve();    
}
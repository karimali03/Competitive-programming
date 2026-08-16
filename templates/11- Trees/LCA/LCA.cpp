struct LCA{
    int LOG,n;
    vii g,up;
    vi lvl;
    LCA(vii &g,int root) :g(g){
        n = g.size();
        LOG = __lg(n) + 1;
        up = vii(n,vi(LOG));
        lvl = vi(n);
        build(root);
    };

    void build(int root){
        up[root][0] = 0;
        lvl[0] = 0;
        for(int i = 1 ; i < LOG; i++) up[root][i] = 0;
        dfs(root,root);
    }

    void dfs(int u,int p){
        for(auto v : g[u]) if(v != p){
            up[v][0] = u;
            lvl[v] = 1 + lvl[u];
            for(int lg = 1 ; lg < LOG ; lg++){
                up[v][lg] = up[up[v][lg-1]][lg-1];
            }
            dfs(v,u);
        }
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
    
    
    // Check if node z is on path from x to y
    bool on_path(int x, int y, int z) {
		int l = lca(x, y);
		int l1 = lca(x, z);
		int l2 = lca(y, z);
		return z == l || (l1 == z && l2 == l) || (l2 == z && l1 == l);
    };
};

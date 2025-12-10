struct LCA {
    // ---------------- CUSTOMIZE HERE ----------------
    // Example: Path Sum
    const long long ID = 0; 
    long long merge(long long a, long long b) { return a + b; }
    // ------------------------------------------------

    int n, LOG;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> up;
    vector<vector<long long>> val; 
    vector<int> lvl;

    LCA(int _n) : n(_n) {
        LOG = 0;
        while ((1 << LOG) <= n) LOG++;
        LOG++; 
        
        adj.resize(n + 1);
        lvl.resize(n + 1);
        up.assign(n + 1, vector<int>(LOG));
        val.assign(n + 1, vector<long long>(LOG, ID));
    }

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    void dfs(int v, int p) {
        for(auto [to, w] : adj[v]) {
            if(to == p) continue;
            
            lvl[to] = lvl[v] + 1;
            up[to][0] = v;
            val[to][0] = w;
            
            for(int j = 1; j < LOG; j++) {
                up[to][j] = up[up[to][j-1]][j-1];
                val[to][j] = merge(val[to][j-1], val[up[to][j-1]][j-1]);
            }
            
            dfs(to, v);
        }
    }

    void build(int root = 1) {
        lvl[root] = 0;
        for(int j = 0; j < LOG; j++) {
            up[root][j] = root; 
            val[root][j] = ID; 
        }
        dfs(root, root);
    }

    int get_kth_ancestor(int u, int k) {
        for (int j = LOG - 1; j >= 0; --j)
            if ((k >> j) & 1) u = up[u][j];
        return u;
    }

    int get_lca(int u, int v) {
        if (lvl[u] < lvl[v]) swap(u, v);
        
        u = get_kth_ancestor(u, lvl[u] - lvl[v]);
        
        if (u == v) return u;
        
        for (int j = LOG - 1; j >= 0; --j) {
            if (up[u][j] != up[v][j]) {
                u = up[u][j];
                v = up[v][j];
            }
        }
        return up[u][0];
    }

    long long query(int u, int v) {
        int lc = get_lca(u, v);
        long long res = ID; 
        
        // 1. Calculate difference for u -> LCA
        int diff1 = lvl[u] - lvl[lc];
        for (int j = LOG - 1; j >= 0; --j) {
            if ((diff1 >> j) & 1) {
                res = merge(res, val[u][j]);
                u = up[u][j];
            }
        }

        // 2. Calculate difference for v -> LCA
        int diff2 = lvl[v] - lvl[lc];
        for (int j = LOG - 1; j >= 0; --j) {
            if ((diff2 >> j) & 1) {
                res = merge(res, val[v][j]);
                v = up[v][j];
            }
        }
        
        return res;
    }
};

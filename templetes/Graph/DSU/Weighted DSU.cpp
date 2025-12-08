struct DSU {
    // dif: Relation of node 'i' to 'par[i]'  
    //  Logic: Value[i] - Value[par[i]] = dif[i]
    vector<int> sz, par, dif;
    int cc; 

    DSU(int n) : cc(n), sz(n, 1), par(n), dif(n, 0) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        int root = get(par[x]); 
        
        // Path Compression: Accumulate weights up to the root.
        // x --- par[x] ---- root
        dif[x] = dif[x] + dif[par[x]]; 
        
        return par[x] = root;
    }

    bool merge(int x, int y, int w) {
        // We are given relation: Value[x] - Value[y] = w
        int rx = get(x), ry = get(y);

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


        if (sz[x] > sz[y]) {
            par[ry] = rx;
            dif[ry] = -cost; 
            sz[rx] += sz[ry];
        } else {
            par[rx] = ry;
            dif[rx] = cost;
            sz[ry] += sz[rx];
        }
        cc--;
        return true;
    }
};

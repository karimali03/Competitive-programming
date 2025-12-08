struct DSU {

    vector<int> sz, par, dif;
    int cc; 

    DSU(int n) : cc(n), sz(n, 1), par(n), dif(n, 0) {
        for (int i = 0; i < n; i++) par[i] = i;
    }

    int get(int x) {
        if (x == par[x]) return x;
        int root = get(par[x]); 

        dif[x] = dif[x] ^ dif[par[x]]; 
        
        return par[x] = root;
    }
    // x y 1  diffrent set
    // x y 0 same set
    bool merge(int x, int y, int w = 0) {
        int rx = get(x), ry = get(y);

        if (rx == ry) {
            return ((dif[x] ^ dif[y]) == w);
        }

        int cost = dif[y] ^ dif[x] ^ w;

        if (sz[x] > sz[y]) {
            par[ry] = rx;
            dif[ry] = cost; 
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

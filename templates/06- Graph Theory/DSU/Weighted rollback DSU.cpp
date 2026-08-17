struct DSU {
    // dif: Relation of node 'i' to 'par[i]'  
    //  Logic: Value[i] - Value[par[i]] = dif[i]
    vector<int> sz, par, dif;
    vector<array<int,3>>history;
    int cc; 

    DSU(int n) : sz(n, 1), par(n), dif(n, 0),cc(n) {
        for (int i = 0; i < n; i++) par[i] = i;
        history.reserve(n);
    }

    pair<int,int> get(int x){
        int d = 0;
        while(x != par[x]){
            // [ x - par[x] ] + [ par[x] - root ]  = x - root 
            d += dif[x];
            x = par[x];
        }        
        return {x,d};
    }

    bool merge(int x, int y, int w) {
        // We are given relation: Value[x] - Value[y] = w
        auto [rx,dx] = get(x);
        auto [ry,dy] = get(y);
        history.push_back({-1,-1,-1});
        // Case 1: Already in same set
        if (rx == ry) {
            // Check consistency. Derived relation must match given 'w'.
            // Logic: (x->root) - (y->root) == (x->y)
            return (dx - dy == w);
        }

        // Case 2: Different sets (Triangle Logic)
        // We need to connect root_x (rx) to root_y (ry).
        // Formula: Path(rx->ry) = Path(rx->x) + Path(x->y) + Path(y->ry)

        int cost = dy - dx + w;
        if (sz[rx] > sz[ry]) {
            par[ry] = rx;
            dif[ry] = -cost; 
            sz[rx] += sz[ry];
            history.back() = {rx,ry,0};
        } else {
            par[rx] = ry;
            dif[rx] = cost;
            sz[ry] += sz[rx];
            history.back() = {rx,ry,1};
        }
        cc--;
        return true;
    }

    void rollback(int state){
        while((int)history.size() > state){
            auto [rx,ry,c] = history.back(); history.pop_back();
            if(rx == -1) continue;
            cc++;
            if(c == 0){
                par[ry] = ry;
                dif[ry] = 0; 
                sz[rx] -= sz[ry];
            }else{
                par[rx] = rx;
                dif[rx] = 0;
                sz[ry] -= sz[rx];
            }
        }
    }

    int state(){
        return history.size();
    }
};

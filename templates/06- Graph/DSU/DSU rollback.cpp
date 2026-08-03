struct dsu {
    vector<int> size, par;
    vector<array<int,2>>history;
    int cc;

    dsu(int n) : size(n, 1), par(n), cc(n) {
        for (int i = 0; i < n; i++) par[i] = i;
        history.reserve(n);
    }

    int get(int x) {
        while(x != par[x]){
            x = par[x];
        }
        return x;
    }

    bool merge(int x, int y) {
        x = get(x);
        y = get(y);
        history.push_back({-1,-1});
        if (x == y) return false;
        if (size[x] > size[y]) swap(x, y);
        par[x] = y;
        size[y] += size[x];
        cc--;
        history.back() = {x,y};
        return true;
    }

    void rollback(){
        auto [x,y] = history.back(); history.pop_back();
        if(x == -1) return;
        cc++;
        size[y] -= size[x];
        par[x] = x;
    }

    void undo(){
        while(history.back()[0] != -2){
            rollback();
        }
        history.pop_back();
    }

};

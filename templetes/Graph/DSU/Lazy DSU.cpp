struct LazyDsu{
    vector<int>par,lazy,sz,res;
    int cnt;
    LazyDsu(int n){
        cnt = n;
        par = lazy = sz = res = vi(2*n+1);
        for(int i = 0;i <= 2*n; i++){
            par[i] = i; sz[i] = 1;
        }
    };

    void apply(int v,int val){
        res[v]+=val; 
        lazy[v]+=val;
    }

    int get(int x){
        if(x == par[x]) return x;
        int p = get(par[x]);
        if(p != par[x]){
            apply(x,lazy[par[x]]);
        }
        return par[x] = p;
    }

    void add(int v,int val){
        apply(get(v),val);
    }

    int getVal(int x){
        int p = get(x);
        return res[x] + (x != par[x] ? lazy[p] : 0);
    }

    bool merge(int x,int y){
        x = get(x) , y = get(y);
        if(x == y) return false;
        int p = cnt++;
        par[x] = par[y] = p;
        lazy[p] = res[p] = 0;
        sz[p] = sz[x] + sz[y] ;
        return true;
    }
};

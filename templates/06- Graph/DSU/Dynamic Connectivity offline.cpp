struct dsu {
    vector<int> size, par;
    vector<array<int,2>>history;
    int cc;
    dsu(){}
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
    int state(){
        return history.size();
    }
    void rollback(int state){
        while((int)history.size() > state){
            auto [x,y] = history.back(); history.pop_back();
            if(x == -1) continue;
            cc++;
            size[y] -= size[x];
            par[x] = x;
        }
    }
};
 
struct SegTree {
    int n;
    vector<vector<array<int,2>>> t; // Tree array
    
    // NEUTRAL VALUE  
    const vector<array<int,2>> VAL_NEUTRAL = {}; // Neutral for tree values (e.g., -2e18 for Max, 0 for Sum)
    dsu ds;
  
    SegTree(int n,int dsu_n) : n(n){
        t.assign(2 * n, VAL_NEUTRAL); 
        ds = dsu(dsu_n);
    }
 
    void apply(int p,array<int,2>& tag) {
        t[p].push_back(tag);
    }
 
    void update(int l, int r,array<int,2>tag) {
        r++; // Adjust for inclusive range
        l += n; r += n;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, tag);
            if (r & 1) apply(--r, tag);
        }
    }
 
 
    void dfs(int u = 1){
        int state = ds.state();
        for(auto [x,y] : t[u]){
            ds.merge(x,y);
        }
        // leaf
        if(u >= n){
            t[u].push_back({ds.cc,0});
        }else{
            dfs(u << 1); // left
            dfs(u << 1 | 1); // right
        }
 
        ds.rollback(state);
    }
};
 
 
void solve() {
    int n,m; cin>>n>>m;
    if(m == 0) return;
    SegTree st(m,n);
    map<array<int,2>,int>mp;
    vector<bool> vld(m);
    for(int i = 0;i  < m; i++){
        char c; cin>>c;
        if(c == '?'){
            vld[i] = true;
        }else if(c == '+'){
            int x,y; cin>>x>>y; x--,y--;
            if(x > y) swap(x,y);
            mp[{x,y}] = i;
        }else if(c == '-'){
            int x,y; cin>>x>>y; x--,y--;
            if(x > y) swap(x,y);
            int start = mp[{x,y}];
            st.update(start,i-1,{x,y});
            mp.erase({x,y});
        }
    }
 
    for(auto &[a,b] : mp){
        st.update(b,m-1,a);
    }
    st.dfs(1);
    for(int i = 0; i < m ; i++){
        if(vld[i]){
            cout<<st.t[i+m].back()[0]<<ln;
        }
    }
}

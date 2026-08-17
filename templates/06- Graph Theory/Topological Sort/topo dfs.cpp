void solve(int test_case) {
    int n,m; cin>>n>>m;
    vii g(n);
    f(i,0,m){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y);
    }
    vi vis(n);
    vi ret;
    bool cycle = 0;
    function<void(int)> dfs = [&](int x){
        vis[x] = 1;
        for(auto it : g[x]){
            if(!vis[it]) dfs(it);
            else if(vis[it] == 1) cycle = 1;
        }
        vis[x] = 2;
        ret.push_back(x+1);
    };
    f(i,0,n) if(!vis[i]) dfs(i);
    if(cycle) NA; // there is no valid topo sort
    else{
        reverse(all(ret));
        cout<<ret<<ln;
    }
}

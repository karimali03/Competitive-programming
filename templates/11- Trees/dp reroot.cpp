void solve(int test_case) {
    int n,MOD; cin>>n>>MOD;
    vii g(n);
    f(i,1,n){
        int x,y; cin>>x>>y; x--,y--;
        g[x].push_back(y); g[y].push_back(x);
    }
    vi dp(n,1);
    function<void(int,int)> rec = [&](int u,int p){
        for(auto v : g[u]){
            if(v == p) continue;
            rec(v,u);
            (dp[u]*=(1+dp[v]))%=MOD;
        }
    };
    rec(0,-1);
    vi ans(n);
    function<void(int,int)> reroot = [&](int u,int p){
        ans[u] = dp[u];
        int sz = g[u].size();
        vi pre(sz+1,1),suf(sz+2,1);
        for(int i = 0 ; i < sz ; i++){
            pre[i+1] = ( pre[i] * (1+dp[g[u][i]]) ) % MOD;
        }
        for(int i = sz-1 ; i >= 0 ; i--){
            suf[i+1] = ( suf[i+2] * (1+dp[g[u][i]]) )%MOD;
        }
        for(int i = 0 ; i < sz ; i++){
            int v = g[u][i];
            if(v == p) continue;
            // make v the root
            int og = dp[u];
            dp[u] = ( pre[i] * suf[i+2] ) % MOD;
            dp[v] = ( dp[v] * (1 + dp[u]) ) % MOD;
            reroot(v,u);
            // return u the root
            dp[u] = og;
        }
    };
}

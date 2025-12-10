vi topo;
void dfs(int x,vii &adj,vi &vis) {
        vis[x] = 1;
        for(auto it : adj[x]) if(!vis[it]) dfs(it,adj,vis);
        topo.push_back(x);
}

vector<int> DAG(int n,vii&g){
    vi vis(n);
    vector<int>().swap(topo);
    for(int i = 0 ; i < n ; i++) if(!vis[i]) dfs(i,g,vis);   
    reverse(all(topo));
    vi prev(n,-1);
    vi dp(n,1);
    for(auto x : topo){
        for(auto it : g[x]){
            if(dp[it] < 1 + dp[x]) prev[it] = x;
            dp[it] = max(dp[it] , 1 + dp[x]);
        } 
    }
    int x = max_element(all(dp)) - dp.begin();
    vi res;
    while(prev[x] != -1){
        res.push_back(x); 
        x = prev[x];
    }
    res.push_back(x);
    return res;
}


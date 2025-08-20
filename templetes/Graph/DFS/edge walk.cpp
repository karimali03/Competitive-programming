 // dfs edge walk (any subset is connected tree  
int n; cin>>n;
vector<vector<int>>adj(n);
vector<int>cur;
for(int i = 0 ;i  < n-1 ; i++){
        int x,y; cin>>x>>y; x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
}
function<void(int,int)> dfs = [&](int x,int p) -> void{
        cur.push_back(x);
        for(auto it : adj[x]){
            if(it == p) continue;
            dfs(it,x);
            cur.push_back(x);
        }
};
dfs(0,-1);

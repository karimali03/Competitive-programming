vector<int> bfs(vii &v,int s){
    int n = v.size();
    queue<int>q;
    q.push(s);
    vi vis(n); vis[s] = 1;
    vi dist(n);
    int lvl = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto x = q.front();
            dist[x] = lvl;
            for(auto it : v[x]){
                if(!vis[it]){
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        lvl++;
    }
    return dist;
}

vector<int> path(vii &v,vi& parent , int u){
    vector<int>res;
    for(int v= u ; v != -1 ; v = parent[v]){
        res.push_back(v);
    }
    reverse(all(res));
    return res;
}
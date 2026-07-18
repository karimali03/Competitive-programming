vector<int> bfs(vii &g,int s){
    queue<int>q;
    q.push(s);
    vi dist(n,-1);  dist[s] = 0;
    int lvl = 0;
    while(!q.empty()){
        int sz = q.size();
        while(sz--){
            auto x = q.front(); q.pop();
            for(auto it : g[x]){
                if(dist[it] == -1){
                    q.push(it);
                    dist[it] = lvl+1;
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

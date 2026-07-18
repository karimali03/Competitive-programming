pair<int, int> bfs(int start,int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    int mx = 0;
    int node = start;
    while(!q.empty()){
        auto cur = q.front(); q.pop();
        for(auto [x,y] : adj[cur]){
            if(dist[x] == -1){
                dist[x] = dist[cur] + 1;
                if(dist[x] > mx){
                    mx = dist[x];
                    node = x;
                }
                q.push(x);
            }
        }
    }
    return {node,mx};
}

int getDiameter(int n) {
    auto [u, _] = bfs(0,n);
    auto [v, diameter] = bfs(u,n);
    return diameter;
}

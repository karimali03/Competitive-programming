// 0-1 BFS
vector<int> d(n, -1);
deque<pair<int,int>> q;
q.push_front({start,0);
while (!q.empty()) {
    auto [cur,cost] = q.front(); q.pop_front();
    if(d[cur] != -1) continue;
    d[cur] = cost;
    for (auto [u,w] : adj[v]) {
        if(w) q.push_back({u,cost+w});
        else q.push_front({u,cost});
    }
}

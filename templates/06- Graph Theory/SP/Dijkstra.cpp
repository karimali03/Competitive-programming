const int INF = 1e9;

struct edge {
    int to, w;

    edge(int to = 0, int w = 0) : to(to), w(w) {}

    bool operator <(const edge &e) const {
        return w > e.w;
    }
};

// O(E logV)
vector<int> Dijkstra(const vector<vector<edge>> &g, int n, int src) {
    vector<int> dist(n, INF);
  
    priority_queue<edge> q; 
    
    q.push(edge(src, 0));
    dist[src] = 0;
    
    while (!q.empty()) {
        edge cur = q.top();  q.pop();
        if (cur.w > dist[cur.to]) continue;

    
        for (auto &it : g[cur.to]) {
          
            if (dist[it.to] > cur.w + it.w) {
                dist[it.to] = cur.w + it.w;
                q.push(edge(it.to, dist[it.to]));
            }
        }
    }

    return dist;
}

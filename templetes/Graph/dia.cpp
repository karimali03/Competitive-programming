pair<int, int> bfs(int start, const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start);
    dist[start] = 0;

    int farthest_node = start;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        for (int neighbor : adj[node]) {
            if (dist[neighbor] == -1) {
                dist[neighbor] = dist[node] + 1;
                q.push(neighbor);
                if (dist[neighbor] > dist[farthest_node]) {
                    farthest_node = neighbor;
                }
            }
        }
    }

    return {farthest_node, dist[farthest_node]}; // node, distance
}

int getDiameter(const vector<vector<int>>& adj) {
    auto [u, _] = bfs(0, adj);
    auto [v, diameter] = bfs(u, adj);
    return diameter;
}


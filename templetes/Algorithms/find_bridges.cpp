struct find_bridges {
    struct edge {
        int node, index;

        edge() {}

        edge(int _node, int _index) : node(_node), index(_index) {}
    };

    int n, edges;
    vector<vector<edge>> adj;
    vector<array<int, 2>> edge_list;
    vector<int> tour_start;
    vector<int> low_link;
    vector<bool> visited;
    vector<bool> is_bridge;
    vector<int> subtree_size;
    int tour;

    find_bridges(int _n = 0) {
        init(_n);
    }

    void init(int _n) {
        n = _n;
        edges = 0;
        adj.assign(n, {});
        edge_list.clear();
        tour_start.resize(n);
        low_link.resize(n);
        subtree_size.resize(n);
        visited.assign(n, false);
        is_bridge.assign(n, false);
        tour = 0;
    }

    void add_edge(int a, int b) {
        adj[a].emplace_back(b, edges);
        adj[b].emplace_back(a, edges);
        edge_list.push_back({a, b});
        edges++;
    }

    void dfs(int node, int parent_edge) {
        assert(!visited[node]);
        visited[node] = true;
        tour_start[node] = tour++;
        low_link[node] = tour_start[node];
        subtree_size[node] = 1;

        for (edge &e : adj[node]) {
            if (e.index == parent_edge)
                continue;

            if (visited[e.node]) {
                low_link[node] = min(low_link[node], tour_start[e.node]);
            } else {
                dfs(e.node, e.index);
                low_link[node] = min(low_link[node], low_link[e.node]);
                is_bridge[e.index] = low_link[e.node] > tour_start[node];
                subtree_size[node] += subtree_size[e.node];
            }
        }
    }
};



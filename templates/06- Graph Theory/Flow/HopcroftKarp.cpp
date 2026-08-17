/*
Hopcroft-Karp — Bipartite Maximum Matching
O(E sqrt(V))

ml[u] = right matched with left u
mr[v] = left matched with right v

Uses:
    - maximum bipartite matching
    - minimum vertex cover
    - maximum independent set
    - DAG minimum path cover

Konig:
    Max Matching = Min Vertex Cover

After max matching:
    alternating BFS from unmatched LEFT
    L -> R : unmatched edges
    R -> L : matched edges
    Min Vertex Cover = unvisited LEFT + visited RIGHT

Bipartite MIS:
    |L| + |R| - max_matching

DAG min path cover:
    n - max_matching
*/
struct HopcroftKarp {
    int n, m;
    vector<vector<int>> g;
    vector<int> ml, mr, dist;

    HopcroftKarp(int n, int m)
        : n(n), m(m), g(n), ml(n, -1), mr(m, -1), dist(n) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        fill(dist.begin(), dist.end(), -1);

        for (int u = 0; u < n; u++) {
            if (ml[u] == -1) {
                dist[u] = 0;
                q.push(u);
            }
        }

        bool found = false;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : g[u]) {
                int nxt = mr[v];

                if (nxt == -1)
                    found = true;
                else if (dist[nxt] == -1) {
                    dist[nxt] = dist[u] + 1;
                    q.push(nxt);
                }
            }
        }

        return found;
    }

    bool dfs(int u) {
        for (int v : g[u]) {
            int nxt = mr[v];

            if (nxt == -1 ||
                (dist[nxt] == dist[u] + 1 && dfs(nxt))) {

                ml[u] = v;
                mr[v] = u;
                return true;
            }
        }

        dist[u] = -1;
        return false;
    }

    int max_matching() {
        int ans = 0;

        while (bfs()) {
            for (int u = 0; u < n; u++)
                if (ml[u] == -1 && dfs(u))
                    ans++;
        }

        return ans;
    }

    vector<pair<int,int>> matching_edges() {
        vector<pair<int,int>> ans;

        for (int u = 0; u < n; u++)
            if (ml[u] != -1)
                ans.push_back({u, ml[u]});

        return ans;
    }

    // {left vertices, right vertices} in minimum vertex cover
    pair<vector<int>, vector<int>> min_vertex_cover() {
        vector<bool> L(n), R(m);
        queue<int> q;

        // start from unmatched LEFT
        for (int u = 0; u < n; u++) {
            if (ml[u] == -1) {
                L[u] = true;
                q.push(u);
            }
        }

        // alternating paths:
        // L -> R through unmatched edges
        // R -> L through matched edges
        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : g[u]) {
                if (ml[u] == v) continue;

                if (!R[v]) {
                    R[v] = true;

                    if (mr[v] != -1 && !L[mr[v]]) {
                        L[mr[v]] = true;
                        q.push(mr[v]);
                    }
                }
            }
        }

        vector<int> left_cover, right_cover;

        // MVC = unvisited LEFT + visited RIGHT
        for (int u = 0; u < n; u++)
            if (!L[u])
                left_cover.push_back(u);

        for (int v = 0; v < m; v++)
            if (R[v])
                right_cover.push_back(v);

        return {left_cover, right_cover};
    }
    
    // LEFT vertices that can become unmatched
    vector<bool> left_swappable() {
        vector<bool> vis(n);
        queue<int> q;

        // start from currently unmatched LEFT vertices
        for (int u = 0; u < n; u++) {
            if (ml[u] == -1) {
                vis[u] = true;
                q.push(u);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            // alternating path:
            // LEFT --unmatched edge--> RIGHT --matched edge--> LEFT
            for (int v : g[u]) {
                if (ml[u] == v) continue;      // need unmatched edge

                int nxt = mr[v];               // matched edge back to LEFT

                if (nxt != -1 && !vis[nxt]) {
                    vis[nxt] = true;
                    q.push(nxt);
                }
            }
        }

        return vis;
    }


    // RIGHT vertices that can become unmatched
    vector<bool> right_swappable() {
        vector<vector<int>> rg(m);

        for (int u = 0; u < n; u++)
            for (int v : g[u])
                rg[v].push_back(u);

        vector<bool> vis(m);
        queue<int> q;

        // start from currently unmatched RIGHT vertices
        for (int v = 0; v < m; v++) {
            if (mr[v] == -1) {
                vis[v] = true;
                q.push(v);
            }
        }

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            // mirror alternating path:
            // RIGHT --unmatched edge--> LEFT --matched edge--> RIGHT
            for (int u : rg[v]) {
                if (mr[v] == u) continue;      // need unmatched edge

                int nxt = ml[u];               // matched edge back to RIGHT

                if (nxt != -1 && !vis[nxt]) {
                    vis[nxt] = true;
                    q.push(nxt);
                }
            }
        }

        return vis;
    }  
};


/*
Swappable vertices in maximum bipartite matching:

A vertex is swappable if it is unmatched, or can become
unmatched without decreasing the maximum matching size.

LEFT swappable:
    start from unmatched LEFT
    L -> R using unmatched edge
    R -> L using matched edge

RIGHT swappable:
    mirror traversal from unmatched RIGHT

Idea:
    flipping an alternating path moves the "free" vertex
    to another vertex while keeping matching size unchanged.

Useful when:
    adding/changing an edge and asking whether matching can increase.
*/
array<int,3> matching_stats() {
    int M = max_matching();

    auto L = left_swappable();
    auto R = right_swappable();

    return {
        M,
        accumulate(L.begin(), L.end(), 0LL),
        accumulate(R.begin(), R.end(), 0LL)
    };
}

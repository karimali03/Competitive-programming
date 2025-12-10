/*
1. Maximum Matching:
   ------------------
A matching is a set of edges where no two edges share a vertex.
A **maximum matching** is the largest such set.
Size of Maximum Matching == Size of Minimum Vertex Cover
"Maximize pairings without overlap"  → Maximum Matching
"Cover all edges with fewest nodes" → Minimum Vertex Cover
-- one indexed
*/

struct HopcroftKarp {
    static const int inf = 1e9;
    
    int n; // Count of Left nodes
    int m; // Count of Right nodes
    
    // l[u]: Stores the Right node matched with Left node u. (0 if unmatched)
    // r[v]: Stores the Left node matched with Right node v. (0 if unmatched)
    // d[u]: Distance array used for BFS logic.
    vector<int> l, r, d;
    
    // g[u]: Adjacency list. g[u] contains indices of Right nodes connected to u.
    // Note: Right node indices are shifted by +n internally (n+1 to n+m).
    vector<vector<int>> g;

    HopcroftKarp(int _n, int _m) {
        n = _n;
        m = _m;
        int p = _n + _m + 1; 
        g.resize(p);
        l.resize(p, 0);
        r.resize(p, 0);
        d.resize(p, 0);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v + n); 
    }

    bool bfs() {
        queue<int> q;
        for (int u = 1; u <= n; u++) {
            if (!l[u]) d[u] = 0, q.push(u);
            else d[u] = inf;
        }
        d[0] = inf;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto v : g[u]) {
                if (d[r[v]] == inf) {
                    d[r[v]] = d[u] + 1;
                    q.push(r[v]);
                }
            }
        }
        return d[0] != inf;
    }

    bool dfs(int u) {
        if (!u) return true;
        for (auto v : g[u]) {
            if (d[r[v]] == d[u] + 1 && dfs(r[v])) {
                l[u] = v;
                r[v] = u;
                return true;
            }
        }
        d[u] = inf;
        return false;
    }
    
    int maximum_matching() {
        int ans = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++)
                if (!l[u] && dfs(u)) ans++;
        }
        return ans;
    }

    // Returns {MaxMatching, LeftSwappable, RightSwappable}
    array<int,3> get_matching_stats() {
        int max_match = maximum_matching();
        if (max_match == n) return {max_match, 0, 0};
        // 1. Find Left Swappable Nodes
        // BFS starts from all Unmatched Left nodes
        vector<bool> vis_left(n + m + 1, false);
        queue<int> q;
        
        for (int i = 1; i <= n; i++) {
            if (l[i] == 0) { // Unmatched
                vis_left[i] = true;
                q.push(i);
            }
        }

        long long left_cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            left_cnt++;

            for (int v : g[u]) {
                int next_u = r[v]; // Follow match back to Left
                if (next_u != 0 && !vis_left[next_u]) {
                    vis_left[next_u] = true;
                    q.push(next_u);
                }
            }
        }

        // 2. Find Right Swappable Nodes
        // BFS starts from all Unmatched Right nodes
        // Requires Reverse Graph (Right -> Left)
        vector<vector<int>> adj_rev(n + m + 1);
        for (int u = 1; u <= n; u++) {
            for (int v : g[u]) {
                adj_rev[v].push_back(u);
            }
        }

        vector<bool> vis_right(n + m + 1, false);
        queue<int> q2;
        
        for (int i = n + 1; i <= n + m; i++) {
            if (r[i] == 0) { // Unmatched
                vis_right[i] = true;
                q2.push(i);
            }
        }

        long long right_cnt = 0;
        while (!q2.empty()) {
            int v = q2.front(); q2.pop();
            right_cnt++;

            for (int u : adj_rev[v]) {
                int next_v = l[u]; // Follow match back to Right
                if (next_v != 0 && !vis_right[next_v]) {
                    vis_right[next_v] = true;
                    q2.push(next_v);
                }
            }
        }
        
        return {max_match, left_cnt, right_cnt};
    }
};

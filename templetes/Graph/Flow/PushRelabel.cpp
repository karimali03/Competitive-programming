// O(v^3) , O(V^2 * E)
const int MAXV = 1005;
const int INF = 1e17;

struct PushRelabel {
    struct Edge {
        int to, rev;
        int cap, flow;
    };

    vector<Edge> adj[MAXV];
    int excess[MAXV], height[MAXV];
    int n, s, t;

    void init(int _n, int _s, int _t) {
        n = _n; s = _s; t = _t;
        for (int i = 0; i < n; ++i)
            adj[i].clear();
    }

    void addEdge(int u, int v, int cap, bool directed = true) {
        adj[u].push_back({v, (int)adj[v].size(), cap, 0});
        adj[v].push_back({u, (int)adj[u].size() - 1, directed ? 0 : cap, 0});
    }

    void push(int u, Edge &e) {
        int v = e.to;
        int d = min(excess[u], e.cap - e.flow);
        if (height[u] == height[v] + 1 && d > 0) {
            e.flow += d;
            adj[v][e.rev].flow -= d;
            excess[u] -= d;
            excess[v] += d;
        }
    }

    void relabel(int u) {
        int d = INF;
        for (Edge &e : adj[u])
            if (e.cap > e.flow)
                d = min(d, height[e.to]);
        if (d < INF)
            height[u] = d + 1;
    }

    void discharge(int u) {
        while (excess[u] > 0) {
            bool pushed = false;
            for (Edge &e : adj[u]) {
                if (e.cap > e.flow && height[u] == height[e.to] + 1) {
                    push(u, e);
                    pushed = true;
                    if (excess[u] == 0) break;
                }
            }
            if (!pushed) relabel(u);
        }
    }

    int maxFlow() {
        fill(excess, excess + n, 0);
        fill(height, height + n, 0);
        height[s] = n;

        for (Edge &e : adj[s]) {
            e.flow = e.cap;
            adj[e.to][e.rev].flow = -e.cap;
            excess[e.to] += e.cap;
            excess[s] -= e.cap;
        }

        vector<int> list;
        for (int i = 0; i < n; ++i)
            if (i != s && i != t) list.push_back(i);

        int p = 0;
        while (p < (int)list.size()) {
            int u = list[p];
            int oldHeight = height[u];
            discharge(u);
            if (height[u] > oldHeight) {
                rotate(list.begin(), list.begin() + p, list.begin() + p + 1);
                p = 0;
            } else {
                ++p;
            }
        }

        return accumulate(adj[s].begin(), adj[s].end(), 0LL, [](int sum, Edge &e) {
            return sum + e.flow;
        });
    }

    vector<vector<int>> paths;

    bool dfs_path(int u, vector<int>& path, vector<bool>& vis) {
        if (u == t) {
            paths.push_back(path);
            return true;
        }
        vis[u] = true;
        for (auto &e : adj[u]) {
            if (e.flow > 0 && !vis[e.to]) {
                path.push_back(e.to);
                e.flow--; // mark flow unit used
                if (dfs_path(e.to, path, vis)) return true;
                path.pop_back();
                e.flow++; // backtrack
            }
        }
        return false;
    }

    vector<vector<int>> getAllFlowPaths() {
        paths.clear();
        while (true) {
            vector<int> path = {s};
            vector<bool> vis(n, false);
            if (!dfs_path(s, path, vis)) break;
        }
        return paths;
    }


    vector<bool> vis;

    void dfs_min_cut(int u) {
        vis[u] = true;
        for (auto &e : adj[u]) {
            if (!vis[e.to] && e.cap > e.flow) { // Residual capacity exists
                dfs_min_cut(e.to);
            }
        }
    }

    vector<pair<int, int>> getMinCut() {
        vis.assign(n, false);
        dfs_min_cut(s);

        vector<pair<int, int>> cut;
        for (int u = 0; u < n; ++u) {
            if (!vis[u]) continue;
            for (auto &e : adj[u]) {
                if (!vis[e.to] && e.cap > 0) {
                    cut.emplace_back(u, e.to); // Edge from reachable to unreachable
                }
            }
        }
        return cut;
    }


    
};



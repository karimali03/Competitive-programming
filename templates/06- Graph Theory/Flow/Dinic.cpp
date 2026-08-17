/*
    1. General Graph (arbitrary capacities):
       - Time: O(V^2 * E)
    2. Unit Capacity Graphs (capacities = 1):
       - Time: O(sqrt(V) * E)
    3. Bounded Small Capacities (e.g., 1 ≤ c ≤ 1000):
       - Time: Better than general case, often around O(min(V^2, E sqrt(V)))
    - Dinic is best for sparse graphs or unit capacity cases
    - For large capacities or dense graphs, use Push-Relabel or Capacity Scaling
*/

using ll = long long;

struct Dinic {
    struct Edge {
        int to, rev;
        ll cap, org;
    };

    int n;
    vector<vector<Edge>> g;
    vector<int> lvl, ptr;

    Dinic(int n) : n(n), g(n), lvl(n), ptr(n) {}

    // returns index of edge inside g[u]
    int add_edge(int u, int v, ll cap) {
        int id = g[u].size();

        g[u].push_back({v, (int)g[v].size(), cap, cap});
        g[v].push_back({u, id, 0, 0});

        return id;
    }

    // capacity c in both directions
    void add_undirected(int u, int v, ll cap) {
        add_edge(u, v, cap);
        add_edge(v, u, cap);
    }

    bool bfs(int s, int t) {
        fill(lvl.begin(), lvl.end(), -1);

        queue<int> q;
        lvl[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto &e : g[u]) {
                if (e.cap && lvl[e.to] == -1) {
                    lvl[e.to] = lvl[u] + 1;
                    q.push(e.to);
                }
            }
        }

        return lvl[t] != -1;
    }

    ll dfs(int u, int t, ll pushed) {
        if (!pushed || u == t) return pushed;

        for (int &i = ptr[u]; i < (int)g[u].size(); i++) {
            Edge &e = g[u][i];

            if (!e.cap || lvl[e.to] != lvl[u] + 1)
                continue;

            ll f = dfs(e.to, t, min(pushed, e.cap));

            if (!f) continue;

            e.cap -= f;
            g[e.to][e.rev].cap += f;

            return f;
        }

        return 0;
    }

    ll max_flow(int s, int t) {
        const ll INF = 4e18;
        ll flow = 0;

        while (bfs(s, t)) {
            fill(ptr.begin(), ptr.end(), 0);

            while (ll f = dfs(s, t, INF))
                flow += f;
        }

        return flow;
    }

    // flow sent through forward edge g[u][id]
    ll edge_flow(int u, int id) {
        return g[u][id].org - g[u][id].cap;
    }

    // reachable vertices from s in residual graph
    vector<bool> min_cut_side(int s) {
        vector<bool> vis(n);
        queue<int> q;

        vis[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (auto &e : g[u]) {
                if (e.cap && !vis[e.to]) {
                    vis[e.to] = true;
                    q.push(e.to);
                }
            }
        }

        return vis;
    }

    // original edges crossing the min cut
    vector<pair<int,int>> min_cut_edges(int s) {
        auto vis = min_cut_side(s);
        vector<pair<int,int>> ans;

        for (int u = 0; u < n; u++) {
            if (!vis[u]) continue;

            for (auto &e : g[u]) {
                if (e.org && !vis[e.to])
                    ans.push_back({u, e.to});
            }
        }

        return ans;
    }
    
    
    // Decompose final flow into {path, amount}
    // Works on a copy, doesn't modify the flow graph.
    vector<pair<vector<int>, ll>> get_flow_paths(int s, int t) {
            vector<vector<ll>> used(n);

            for (int u = 0; u < n; u++) {
                used[u].resize(g[u].size());
                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto &e = g[u][i];
                    if (e.org)
                        used[u][i] = e.org - e.cap;
                }
            }

            vector<pair<vector<int>, ll>> paths;

            while (true) {
                vector<int> par(n, -1), pe(n, -1);
                queue<int> q;

                par[s] = s;
                q.push(s);

                while (!q.empty() && par[t] == -1) {
                    int u = q.front();
                    q.pop();

                    for (int i = 0; i < (int)g[u].size(); i++) {
                        auto &e = g[u][i];

                        if (used[u][i] > 0 && par[e.to] == -1) {
                            par[e.to] = u;
                            pe[e.to] = i;
                            q.push(e.to);
                        }
                    }
                }

                if (par[t] == -1) break;

                ll f = 4e18;

                for (int v = t; v != s; v = par[v])
                    f = min(f, used[par[v]][pe[v]]);

                vector<int> path;

                for (int v = t;; v = par[v]) {
                    path.push_back(v);
                    if (v == s) break;
                }

                reverse(path.begin(), path.end());

                for (int v = t; v != s; v = par[v])
                    used[par[v]][pe[v]] -= f;

                paths.push_back({path, f});
            }

            return paths;
    }
};

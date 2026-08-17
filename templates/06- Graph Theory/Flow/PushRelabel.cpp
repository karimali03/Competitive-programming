/*
Push-Relabel — Max Flow

Idea:
    allow temporary excess flow at vertices

excess[v]:
    incoming - outgoing

height[v]:
    flow can push only:
        height[u] = height[v] + 1

push:
    send min(excess[u], residual capacity)

relabel:
    height[u] =
        1 + min(height[v])
    over residual neighbors

Initialization:
    height[S] = n
    saturate all edges from S

Answer:
    excess[T]

Use:
    alternative to Dinic
    often strong on dense/heavy max-flow graphs
*/
using ll = long long;

struct PushRelabel {
    struct Edge {
        int to, rev;
        ll cap, org;
    };

    int n;
    vector<vector<Edge>> g;
    vector<ll> excess;
    vector<int> height, ptr;
    vector<bool> active;
    queue<int> q;

    PushRelabel(int n)
        : n(n), g(n), excess(n), height(n),
          ptr(n), active(n) {}

    int add_edge(int u, int v, ll cap) {
        int id = g[u].size();

        g[u].push_back({v, (int)g[v].size(), cap, cap});
        g[v].push_back({u, id, 0, 0});

        return id;
    }

    ll edge_flow(int u, int id) {
        return g[u][id].org - g[u][id].cap;
    }

    void push(int u, Edge &e) {
        if (!excess[u] || !e.cap ||
            height[u] != height[e.to] + 1)
            return;

        ll f = min(excess[u], e.cap);

        e.cap -= f;
        g[e.to][e.rev].cap += f;

        excess[u] -= f;
        excess[e.to] += f;

        if (!active[e.to] && excess[e.to] > 0) {
            active[e.to] = true;
            q.push(e.to);
        }
    }

    void relabel(int u) {
        int mn = INT_MAX;

        for (auto &e : g[u])
            if (e.cap)
                mn = min(mn, height[e.to]);

        if (mn != INT_MAX)
            height[u] = mn + 1;
    }

    void discharge(int u) {
        while (excess[u] > 0) {
            if (ptr[u] == (int)g[u].size()) {
                relabel(u);
                ptr[u] = 0;
                continue;
            }

            Edge &e = g[u][ptr[u]];

            if (e.cap && height[u] == height[e.to] + 1)
                push(u, e);
            else
                ptr[u]++;
        }
    }

    ll max_flow(int s, int t) {
        fill(excess.begin(), excess.end(), 0);
        fill(height.begin(), height.end(), 0);
        fill(ptr.begin(), ptr.end(), 0);
        fill(active.begin(), active.end(), false);

        while (!q.empty()) q.pop();

        height[s] = n;
        active[s] = active[t] = true;

        // saturate edges from source
        for (auto &e : g[s]) {
            if (!e.cap) continue;

            ll f = e.cap;

            e.cap -= f;
            g[e.to][e.rev].cap += f;

            excess[s] -= f;
            excess[e.to] += f;

            if (e.to != t && !active[e.to]) {
                active[e.to] = true;
                q.push(e.to);
            }
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            active[u] = false;
            discharge(u);

            if (excess[u] > 0 && !active[u]) {
                active[u] = true;
                q.push(u);
            }
        }

        return excess[t];
    }

    // ---------------- Flow Paths ----------------

    // Decompose s->t flow into {path, amount}
    // Doesn't modify the actual graph.
    vector<pair<vector<int>, ll>>
    get_flow_paths(int s, int t) {
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

            if (par[t] == -1)
                break;

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

    // ---------------- Min Cut ----------------

    // vertices on source side of minimum cut
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

    // original edges crossing S-side -> T-side
    vector<pair<int,int>> getMinCut(int s) {
        auto vis = min_cut_side(s);

        vector<pair<int,int>> cut;

        for (int u = 0; u < n; u++) {
            if (!vis[u]) continue;

            for (auto &e : g[u]) {
                if (e.org && !vis[e.to])
                    cut.push_back({u, e.to});
            }
        }

        return cut;
    }
};

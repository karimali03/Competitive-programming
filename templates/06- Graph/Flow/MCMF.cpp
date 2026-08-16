/*
Min-Cost Max-Flow

Edge:
    capacity + cost

Residual reverse edge:
    cap = 0
    cost = -cost

Goal:
    min_cost_flow(s,t)
        -> maximum flow with minimum cost

    min_cost_flow(s,t,K)
        -> send exactly K with minimum cost
        -> impossible if flow < K

Dijkstra uses reduced cost:
    cost + pot[u] - pot[v]

Negative original costs:
    initialize potentials with Bellman-Ford

Maximize profit:
    cost = -profit

Useful for:
    - weighted assignment
    - K assignments with minimum cost
    - transportation with costs
    - capacities + costs
    - maximize profit under flow constraints

edge_flow(u,id):
    original capacity - residual capacity
*/
using ll = long long;
struct MCMF {
    struct Edge {
        int to, rev;
        ll cap, cost, org;
    };

    int n;
    bool has_neg = false;
    vector<vector<Edge>> g;

    MCMF(int n) : n(n), g(n) {}

    // returns edge index inside g[u]
    int add_edge(int u, int v, ll cap, ll cost) {
        int id = g[u].size();

        g[u].push_back({v, (int)g[v].size(), cap, cost, cap});
        g[v].push_back({u, id, 0, -cost, 0});

        if (cost < 0) has_neg = true;

        return id;
    }

    ll edge_flow(int u, int id) {
        return g[u][id].org - g[u][id].cap;
    }

    pair<ll,ll> min_cost_flow(int s, int t, ll need = 4e18) {
        const ll INF = 4e18;

        vector<ll> pot(n), dist(n);
        vector<int> pv(n), pe(n);

        // Initial potentials if original negative edges exist
        if (has_neg) {
            fill(pot.begin(), pot.end(), INF);
            pot[s] = 0;

            for (int it = 0; it < n - 1; it++) {
                bool changed = false;

                for (int u = 0; u < n; u++) {
                    if (pot[u] == INF) continue;

                    for (auto &e : g[u]) {
                        if (e.cap && pot[e.to] > pot[u] + e.cost) {
                            pot[e.to] = pot[u] + e.cost;
                            changed = true;
                        }
                    }
                }

                if (!changed) break;
            }

            for (auto &x : pot)
                if (x == INF) x = 0;
        }

        ll flow = 0, cost = 0;

        while (flow < need) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;

            priority_queue<
                pair<ll,int>,
                vector<pair<ll,int>>,
                greater<pair<ll,int>>
            > pq;

            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d != dist[u]) continue;

                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto &e = g[u][i];

                    if (!e.cap) continue;

                    ll nd = d + e.cost + pot[u] - pot[e.to];

                    if (nd < dist[e.to]) {
                        dist[e.to] = nd;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }

            if (dist[t] == INF) break;

            for (int v = 0; v < n; v++)
                if (dist[v] < INF)
                    pot[v] += dist[v];

            ll f = need - flow;

            for (int v = t; v != s; v = pv[v])
                f = min(f, g[pv[v]][pe[v]].cap);

            for (int v = t; v != s; v = pv[v]) {
                Edge &e = g[pv[v]][pe[v]];

                cost += f * e.cost;

                e.cap -= f;
                g[e.to][e.rev].cap += f;
            }

            flow += f;
        }

        return {flow, cost};
    }
};


// decompose the final s-t flow into paths
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

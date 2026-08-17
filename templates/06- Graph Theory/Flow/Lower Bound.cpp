/*
======================= LOWER BOUND FLOW =======================

Edge:
    L <= flow(u,v) <= R

Transform:
    add capacity (R-L)
    bal[u] -= L
    bal[v] += L

Actual flow:
    low + extra_flow

Feasible circulation:
    bal[v] > 0 -> SS -> v
    bal[v] < 0 -> v -> TT

    feasible iff all flow from SS is saturated.

S -> T flow with lower bounds:
    add T -> S (INF)
    check circulation feasibility
    flow on T -> S = initial feasible S->T flow
    remove auxiliary edges
    run normal maxflow(S,T)

Flow paths:
    use ACTUAL flow = low + extra flow
    decomposition returns S->T paths; cycles are ignored.

Min cut after max S->T flow:
    reachable from S in final residual graph = S side

For lower bounds, cut value is:

    sum upper(u->v), u in S-side, v in T-side
  - sum lower(u->v), u in T-side, v in S-side
===============================================================
*/

struct LowerBoundFlow {
    using ll = long long;
    static constexpr ll INF = (ll)4e18;

    struct Edge {
        int u, v;
        int id;          // edge id inside mf.g[u]
        ll low, high;
    };

    struct MinCut {
        vector<bool> side;

        // indices in edges[]
        vector<int> forward;   // S-side -> T-side
        vector<int> backward;  // T-side -> S-side

        ll value;
    };

    int n, SS, TT;
    Dinic mf;

    vector<ll> bal;
    vector<Edge> edges;

    vector<pair<int,int>> aux_edges;

    bool prepared = false;
    bool st_ready = false;

    ll base_flow = 0;

    LowerBoundFlow(int n)
        : n(n), SS(n), TT(n + 1),
          mf(n + 2), bal(n) {}

    // ---------------------------------------------------------
    // Add L <= flow(u,v) <= R
    // returns index inside edges[]
    // ---------------------------------------------------------

    int add_edge(int u, int v, ll L, ll R) {
        assert(0 <= L && L <= R);
        assert(!prepared);

        int id = mf.add_edge(u, v, R - L);

        bal[u] -= L;
        bal[v] += L;

        edges.push_back({u, v, id, L, R});

        return (int)edges.size() - 1;
    }

    // ---------------------------------------------------------
    // Actual flow on an ORIGINAL lower-bound edge
    // ---------------------------------------------------------

    ll edge_flow(int idx) {
        auto &e = edges[idx];

        return e.low + mf.edge_flow(e.u, e.id);
    }

private:

    // completely remove an auxiliary edge from residual graph
    void disable_edge(int u, int id) {
        auto &e = mf.g[u][id];
        auto &rev = mf.g[e.to][e.rev];

        e.cap = 0;
        rev.cap = 0;
    }

    ll add_balance_edges() {
        ll need = 0;

        for (int v = 0; v < n; v++) {
            if (bal[v] > 0) {
                int id = mf.add_edge(SS, v, bal[v]);
                aux_edges.push_back({SS, id});

                need += bal[v];
            }
            else if (bal[v] < 0) {
                int id = mf.add_edge(v, TT, -bal[v]);
                aux_edges.push_back({v, id});
            }
        }

        return need;
    }

    void remove_auxiliary_edges() {
        for (auto [u, id] : aux_edges)
            disable_edge(u, id);

        aux_edges.clear();
    }

public:

    // =========================================================
    // 1) FEASIBLE CIRCULATION
    // =========================================================

    bool feasible_circulation() {
        assert(!prepared);
        prepared = true;

        ll need = add_balance_edges();

        return mf.max_flow(SS, TT) == need;
    }

    // =========================================================
    // 2) MAXIMUM S -> T FLOW WITH LOWER BOUNDS
    // =========================================================

    pair<bool,ll> max_flow(int s, int t) {
        assert(!prepared);
        prepared = true;

        // close S->T flow into a circulation
        int back_id = mf.add_edge(t, s, INF);

        ll need = add_balance_edges();

        if (mf.max_flow(SS, TT) != need)
            return {false, 0};

        // flow through T -> S represents initial feasible S->T flow
        base_flow = mf.edge_flow(t, back_id);

        // remove SS, TT edges
        remove_auxiliary_edges();

        // remove special T -> S edge and its residual reverse
        disable_edge(t, back_id);

        st_ready = true;

        ll extra = mf.max_flow(s, t);

        return {true, base_flow + extra};
    }

    // =========================================================
    // 3) FLOW PATH DECOMPOSITION
    // =========================================================

    vector<pair<vector<int>,ll>>
    get_flow_paths(int s, int t) {
        vector<vector<pair<int,ll>>> g2(n);

        // only ORIGINAL edges
        for (int i = 0; i < (int)edges.size(); i++) {
            auto &e = edges[i];

            ll f = edge_flow(i);

            if (f > 0)
                g2[e.u].push_back({i, f});
        }

        vector<ll> used(edges.size());

        for (int i = 0; i < (int)edges.size(); i++)
            used[i] = edge_flow(i);

        vector<pair<vector<int>,ll>> paths;

        while (true) {
            vector<int> par(n, -1);
            vector<int> pe(n, -1);

            queue<int> q;
            q.push(s);
            par[s] = s;

            while (!q.empty() && par[t] == -1) {
                int u = q.front();
                q.pop();

                for (auto [id, _] : g2[u]) {
                    if (!used[id]) continue;

                    int v = edges[id].v;

                    if (par[v] == -1) {
                        par[v] = u;
                        pe[v] = id;
                        q.push(v);
                    }
                }
            }

            if (par[t] == -1)
                break;

            ll f = INF;

            for (int v = t; v != s; v = par[v])
                f = min(f, used[pe[v]]);

            vector<int> path;

            for (int v = t;; v = par[v]) {
                path.push_back(v);

                if (v == s)
                    break;
            }

            reverse(path.begin(), path.end());

            for (int v = t; v != s; v = par[v])
                used[pe[v]] -= f;

            paths.push_back({path, f});
        }

        return paths;
    }

    // =========================================================
    // 4) MIN CUT SIDE
    // =========================================================

    vector<bool> min_cut_side(int s) {
        assert(st_ready);

        return mf.min_cut_side(s);
    }

    // =========================================================
    // 5) MIN CUT WITH LOWER BOUNDS
    // =========================================================

    MinCut getMinCut(int s) {
        assert(st_ready);

        auto side = mf.min_cut_side(s);

        MinCut cut;
        cut.side = side;
        cut.value = 0;

        for (int i = 0; i < (int)edges.size(); i++) {
            auto &e = edges[i];

            // S-side -> T-side:
            // contributes UPPER bound
            if (side[e.u] && !side[e.v]) {
                cut.forward.push_back(i);
                cut.value += e.high;
            }

            // T-side -> S-side:
            // subtract LOWER bound
            else if (!side[e.u] && side[e.v]) {
                cut.backward.push_back(i);
                cut.value -= e.low;
            }
        }

        return cut;
    }
};

#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const ll INF = 4e18;

struct Edge {
    int u, v;
    ll w;
};

/*
========================================================
1) NORMAL BELLMAN-FORD
========================================================

Use:
- Single source shortest paths
- Negative edges allowed
- No need to handle negative cycles specially

Complexity:
O(V * E)
with early stopping.

Returns:
INF -> unreachable
otherwise shortest distance
*/

vector<ll> bellman(
    int n,
    const vector<Edge>& edges,
    int src
) {
    vector<ll> d(n, INF);
    d[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;

        for (auto [u, v, w] : edges) {
            if (d[u] == INF) continue;

            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    return d;
}


/*
========================================================
2) NEGATIVE CYCLE REACHABLE FROM SOURCE
========================================================

Use:
- Need to know whether a negative cycle is reachable
  from src.
- Returns one such cycle.

Complexity:
O(V * E)

Returns:
{} -> no reachable negative cycle

Otherwise:
cycle vertices, with first vertex repeated at end.

Example:
2 5 7 2
*/

vector<int> neg_cycle_from_src(
    int n,
    const vector<Edge>& edges,
    int src
) {
    vector<ll> d(n, INF);
    vector<int> par(n, -1);

    d[src] = 0;

    int x = -1;

    for (int i = 0; i < n; i++) {
        x = -1;

        for (auto [u, v, w] : edges) {
            if (d[u] == INF) continue;

            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                par[v] = u;
                x = v;
            }
        }

        // No changes -> negative cycle impossible
        if (x == -1)
            return {};
    }

    /*
        x was relaxed on iteration n.

        x may only be reachable FROM the cycle.

        Jump n parents to guarantee we enter the cycle.
    */
    for (int i = 0; i < n; i++)
        x = par[x];

    vector<int> cyc;

    int v = x;

    do {
        cyc.push_back(v);
        v = par[v];
    } while (v != x);

    cyc.push_back(x);

    // Parent pointers go backwards.
    reverse(cyc.begin(), cyc.end());

    return cyc;
}


/*
========================================================
3) FIND ANY NEGATIVE CYCLE IN THE GRAPH
========================================================

Use:
- Negative cycle may be in any disconnected component.
- No source is given.

Trick:
Set all dist = 0.

Equivalent to:
super_source --0--> every vertex

Complexity:
O(V * E)

Returns:
{} -> no negative cycle
otherwise one negative cycle.
*/

vector<int> any_neg_cycle(
    int n,
    const vector<Edge>& edges
) {
    // Every node acts as initially reachable.
    vector<ll> d(n, 0);
    vector<int> par(n, -1);

    int x = -1;

    for (int i = 0; i < n; i++) {
        x = -1;

        for (auto [u, v, w] : edges) {
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                par[v] = u;
                x = v;
            }
        }

        if (x == -1)
            return {};
    }

    // Enter the cycle.
    for (int i = 0; i < n; i++)
        x = par[x];

    vector<int> cyc;

    int v = x;

    do {
        cyc.push_back(v);
        v = par[v];
    } while (v != x);

    cyc.push_back(x);

    reverse(cyc.begin(), cyc.end());

    return cyc;
}


/*
========================================================
4) SHORTEST PATH + NEGATIVE CYCLE EFFECT
========================================================

Use:
Need to classify every vertex:

INF  -> unreachable
-INF -> shortest path = -infinity
       because reachable negative cycle can reach it
else -> finite shortest distance

Bellman part:
O(V * E)

Negative cycle propagation:
O(V + E)

Total:
O(V * E)
*/

vector<ll> bellman_neg_inf(
    int n,
    const vector<Edge>& edges,
    int src
) {
    vector<ll> d(n, INF);

    // Normal graph needed for BFS propagation.
    vector<vector<int>> g(n);

    for (auto [u, v, w] : edges)
        g[u].push_back(v);

    d[src] = 0;

    vector<int> bad(n, 0);

    for (int i = 0; i < n; i++) {
        bool changed = false;

        for (auto [u, v, w] : edges) {
            if (d[u] == INF) continue;

            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                changed = true;

                /*
                    Relaxed on nth iteration:
                    affected by some reachable negative cycle.
                */
                if (i == n - 1)
                    bad[v] = 1;
            }
        }

        if (!changed)
            break;
    }

    /*
        Anything reachable from a bad vertex
        is also -INF.
    */
    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (bad[i])
            q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : g[u]) {
            if (bad[v]) continue;

            bad[v] = 1;
            q.push(v);
        }
    }

    for (int i = 0; i < n; i++) {
        if (bad[i])
            d[i] = -INF;
    }

    return d;
}


/*
========================================================
5) SHORTEST PATH USING AT MOST K EDGES
========================================================

Use:
"Find shortest path using at most k edges/flights/etc."

Important:
Must use PREVIOUS iteration distances.

Don't relax directly into d[].

Complexity:
O(K * E)
*/

vector<ll> bellman_k_edges(
    int n,
    const vector<Edge>& edges,
    int src,
    int k
) {
    vector<ll> d(n, INF);
    d[src] = 0;

    for (int step = 0; step < k; step++) {
        vector<ll> nd = d;

        for (auto [u, v, w] : edges) {
            if (d[u] == INF) continue;

            nd[v] = min(
                nd[v],
                d[u] + w
            );
        }

        d.swap(nd);
    }

    return d;
}


/*
========================================================
6) BELLMAN + PATH RECONSTRUCTION
========================================================

Use:
Need shortest distances AND path.

Only intended when shortest paths are well-defined
(no relevant negative cycle).

Complexity:
O(V * E)
*/

pair<vector<ll>, vector<int>> bellman_with_parent(
    int n,
    const vector<Edge>& edges,
    int src
) {
    vector<ll> d(n, INF);
    vector<int> par(n, -1);

    d[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;

        for (auto [u, v, w] : edges) {
            if (d[u] == INF) continue;

            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                par[v] = u;
                changed = true;
            }
        }

        if (!changed)
            break;
    }

    return {d, par};
}


/*
Reconstruct src -> target.

Returns:
{} if target unreachable.
*/

vector<int> restore_path(
    int src,
    int target,
    const vector<int>& par
) {
    vector<int> path;

    for (int v = target; v != -1; v = par[v])
        path.push_back(v);

    reverse(path.begin(), path.end());

    if (path.empty() || path[0] != src)
        return {};

    return path;
}

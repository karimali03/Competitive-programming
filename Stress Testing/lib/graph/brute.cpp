#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Nodes are 1..n. Edge lists are vector<pii> (u, v). Weights are a parallel vi w (w[i] for e[i]).
const ll INF = 1e18;

// ---- Floyd-Warshall ----
// All-pairs shortest paths, directed edges u->v. d[i][j] = INF if no path. O(n^3), n <= 100.
// Assumes no negative cycle; if d[i][i] < 0 for some i then a negative cycle exists (values clamped at -INF).
vector<vector<ll>> floyd(int n, const vector<pii>& e, const vi& w) {
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, INF));
    for (int i = 1; i <= n; i++) d[i][i] = 0;
    for (size_t i = 0; i < e.size(); i++) d[e[i].first][e[i].second] = min(d[e[i].first][e[i].second], (ll)w[i]);
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
        if (d[i][k] < INF && d[k][j] < INF) d[i][j] = min(d[i][j], max(d[i][k] + d[k][j], -INF));
    return d;
}

// ---- Bellman-Ford ----
// Single-source shortest paths from s, directed edges. dist = INF if unreachable. O(n*m), n <= 1000.
// Returns an empty vector if a negative cycle is reachable from s.
vector<ll> bellmanFord(int n, const vector<pii>& e, const vi& w, int s) {
    vector<ll> d(n + 1, INF);
    d[s] = 0;
    for (int it = 0; it <= n; it++) {
        bool ch = false;
        for (size_t i = 0; i < e.size(); i++)
            if (d[e[i].first] < INF && d[e[i].first] + w[i] < d[e[i].second])
                d[e[i].second] = d[e[i].first] + w[i], ch = true;
        if (!ch) return d;
    }
    return {}; // still relaxing after n+1 rounds
}

// ---- components ----
// Undirected components counted with DSU, ignoring edge number skipE and node skipV (-1 / 0 = skip nothing).
// O(m * a(n)). Count = (#nodes not skipped) - (#successful unions).
int countComps(int n, const vector<pii>& e, int skipE = -1, int skipV = 0) {
    vi p(n + 1);
    iota(p.begin(), p.end(), 0);
    function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
    int c = n - (skipV != 0);
    for (int i = 0; i < (int)e.size(); i++) {
        int a = e[i].first, b = e[i].second;
        if (i == skipE || a == skipV || b == skipV) continue;
        if (f(a) != f(b)) p[f(a)] = f(b), c--;
    }
    return c;
}

// ---- bridges / articulation points ----
// Indices of edges whose removal increases the number of components. O(m * (n+m)), n,m <= 200.
vi bridges(int n, const vector<pii>& e) {
    vi r;
    int base = countComps(n, e);
    for (int i = 0; i < (int)e.size(); i++) if (countComps(n, e, i) > base) r.push_back(i);
    return r;
}
// Nodes whose removal increases the number of components. O(n * (n+m)), n,m <= 200.
vi artPoints(int n, const vector<pii>& e) {
    vi r;
    int base = countComps(n, e);
    for (int v = 1; v <= n; v++) if (countComps(n, e, -1, v) > base) r.push_back(v);
    return r;
}

// ---- reachability / SCC ----
// reach[i][j] = 1 iff directed path i -> j (reach[i][i] = 1). O(n^3), n <= 100.
vector<vi> reach(int n, const vector<pii>& e) {
    vector<vi> r(n + 1, vi(n + 1, 0));
    for (int i = 1; i <= n; i++) r[i][i] = 1;
    for (auto [a, b] : e) r[a][b] = 1;
    for (int k = 1; k <= n; k++) for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++)
        if (r[i][k] && r[k][j]) r[i][j] = 1;
    return r;
}
// SCC id of every node = smallest node mutually reachable with it (like KACTL stress-tests/graph/SCC.cpp). O(n^3).
vi sccMinNode(int n, const vector<pii>& e) {
    vector<vi> r = reach(n, e);
    vi c(n + 1, 0);
    for (int i = 1; i <= n; i++)
        for (int j = n; j >= 1; j--) if (r[i][j] && r[j][i]) c[i] = j;
    return c;
}

// ---- DAG / topological order ----
// True iff the directed graph has no cycle (repeatedly delete a node with no incoming edge). O(n*(n+m)).
bool isDAG(int n, const vector<pii>& e) {
    vi gone(n + 1, 0);
    for (int it = 0; it < n; it++) {
        vi hasIn(n + 1, 0);
        for (auto [a, b] : e) if (!gone[a] && !gone[b]) hasIn[b] = 1;
        int v = 0;
        for (int i = 1; i <= n && !v; i++) if (!gone[i] && !hasIn[i]) v = i;
        if (!v) return false;
        gone[v] = 1;
    }
    return true;
}
// True iff order (a permutation of 1..n) lists u before v for every edge u->v. O(n+m).
bool isTopoOrder(int n, const vector<pii>& e, const vi& order) {
    if ((int)order.size() != n) return false;
    vi pos(n + 1, -1);
    for (int i = 0; i < n; i++) {
        if (order[i] < 1 || order[i] > n || pos[order[i]] != -1) return false;
        pos[order[i]] = i;
    }
    for (auto [a, b] : e) if (pos[a] >= pos[b]) return false;
    return true;
}

// ---- bipartite check ----
// True iff nodes can be 2-colored with no edge inside a color (tries all colorings). O(2^n * m), n <= 20.
bool isBipartite(int n, const vector<pii>& e) {
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (auto [a, b] : e) if ((mask >> (a - 1) & 1) == (mask >> (b - 1) & 1)) ok = false;
        if (ok) return true;
    }
    return false;
}

// ---- MST ----
// Min spanning tree weight: tries every (n-1)-edge subset, keeps those that join everything. -1 if disconnected.
// O(2^m * m), m <= 18.
ll mstWeight(int n, const vector<pii>& e, const vi& w) {
    int m = e.size();
    ll best = INF;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount(mask) != n - 1) continue;
        vi p(n + 1);
        iota(p.begin(), p.end(), 0);
        function<int(int)> f = [&](int x) { return p[x] == x ? x : p[x] = f(p[x]); };
        ll s = 0;
        int merged = 0;
        for (int i = 0; i < m; i++) if (mask >> i & 1) {
            s += w[i];
            if (f(e[i].first) != f(e[i].second)) p[f(e[i].first)] = f(e[i].second), merged++;
        }
        if (merged == n - 1) best = min(best, s);
    }
    return best == INF ? -1 : best;
}

// ---- max matching ----
// Max matching size in a general graph: DP over subsets of matched nodes. From KACTL stress-tests/graph/GeneralMatching.cpp.
// O(2^n * m), n <= 20.
int maxMatching(int n, const vector<pii>& e) {
    vi dp(1 << n);
    for (int m = 0; m < (1 << n); m++) for (auto [a, b] : e) {
        int bits = 1 << (a - 1) | 1 << (b - 1);
        if (!(m & bits)) dp[m | bits] = max(dp[m | bits], dp[m] + 1);
    }
    return *max_element(dp.begin(), dp.end());
}

// ---- independent set / clique / vertex cover ----
// Max independent set size (no two chosen nodes adjacent). O(2^n * n), n <= 20.
int maxIndSet(int n, const vector<pii>& e) {
    vi adj(n, 0);
    for (auto [a, b] : e) adj[a - 1] |= 1 << (b - 1), adj[b - 1] |= 1 << (a - 1);
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i < n; i++) if ((mask >> i & 1) && (adj[i] & mask)) ok = false;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    return best;
}
// Max clique size (all chosen nodes pairwise adjacent). O(2^n * n), n <= 20.
int maxClique(int n, const vector<pii>& e) {
    vi adj(n, 0);
    for (auto [a, b] : e) adj[a - 1] |= 1 << (b - 1), adj[b - 1] |= 1 << (a - 1);
    int best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (int i = 0; i < n; i++) if ((mask >> i & 1) && ((adj[i] | 1 << i) & mask) != mask) ok = false;
        if (ok) best = max(best, __builtin_popcount(mask));
    }
    return best;
}
// Min vertex cover size (every edge has a chosen endpoint). O(2^n * m), n <= 20. (= n - maxIndSet)
int minVertexCover(int n, const vector<pii>& e) {
    int best = n;
    for (int mask = 0; mask < (1 << n); mask++) {
        bool ok = true;
        for (auto [a, b] : e) if (!(mask >> (a - 1) & 1) && !(mask >> (b - 1) & 1)) ok = false;
        if (ok) best = min(best, __builtin_popcount(mask));
    }
    return best;
}

// ---- max flow (= min cut) ----
// Max flow s -> t in a directed graph with capacities w, as the min cut over all node sets S with s in S, t not in S.
// O(2^n * m), n <= 15. Requires s != t.
ll maxFlow(int n, const vector<pii>& e, const vi& w, int s, int t) {
    ll best = INF;
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!(mask >> (s - 1) & 1) || (mask >> (t - 1) & 1)) continue;
        ll c = 0;
        for (size_t i = 0; i < e.size(); i++)
            if ((mask >> (e[i].first - 1) & 1) && !(mask >> (e[i].second - 1) & 1)) c += w[i];
        best = min(best, c);
    }
    return best;
}

// ---- 2-SAT ----
// Is there an assignment satisfying all clauses (a or b)? Literal +x = x true, -x = x false (vars 1..n).
// Tries all assignments. O(2^n * m), n <= 20.
bool sat2(int n, const vector<pii>& clauses) {
    for (int mask = 0; mask < (1 << n); mask++) {
        auto val = [&](int l) { return (mask >> (abs(l) - 1) & 1) == (l > 0); };
        bool ok = true;
        for (auto [a, b] : clauses) if (!val(a) && !val(b)) ok = false;
        if (ok) return true;
    }
    return false;
}

// ---- Euler trail / circuit ----
// Is there a trail using every edge exactly once? circuit = true: it must also end where it started.
// dir = true: edges are u->v, else undirected. Backtracking from every start. O(m!), m <= 10.
bool hasEuler(int n, const vector<pii>& e, bool circuit, bool dir) {
    int m = e.size();
    vi used(m, 0);
    function<bool(int, int, int)> go = [&](int s, int v, int cnt) {
        if (cnt == m) return !circuit || v == s;
        for (int i = 0; i < m; i++) if (!used[i]) {
            int to = -1;
            if (e[i].first == v) to = e[i].second;
            else if (!dir && e[i].second == v) to = e[i].first;
            if (to < 0) continue;
            used[i] = 1;
            bool ok = go(s, to, cnt + 1);
            used[i] = 0;
            if (ok) return true;
        }
        return false;
    };
    for (int s = 1; s <= n; s++) if (go(s, s, 0)) return true;
    return false;
}

// ---- number of shortest paths ----
// Directed graph, positive weights: {shortest dist s->t, number of shortest paths}; {INF, 0} if unreachable.
// Enumerates all simple paths. O(paths), n <= 9.
pair<ll, ll> shortestPaths(int n, const vector<pii>& e, const vi& w, int s, int t) {
    pair<ll, ll> best = {INF, 0};
    vi vis(n + 1, 0);
    function<void(int, ll)> go = [&](int v, ll d) {
        if (v == t) {
            if (d < best.first) best = {d, 1};
            else if (d == best.first) best.second++;
            return;
        }
        vis[v] = 1;
        for (size_t i = 0; i < e.size(); i++) if (e[i].first == v && !vis[e[i].second]) go(e[i].second, d + w[i]);
        vis[v] = 0;
    };
    go(s, 0);
    return best;
}

int main() {
    // reads what gen.cpp prints: "n m" then m lines "u v w" (directed, weighted)
    int n, m;
    cin >> n >> m;
    vector<pii> e(m);
    vi w(m);
    for (int i = 0; i < m; i++) cin >> e[i].first >> e[i].second >> w[i];
    vector<vector<ll>> d = floyd(n, e, w);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (d[i][j] == INF) cout << "inf ";
            else cout << d[i][j] << ' ';
        }
        cout << '\n';
    }
}

/* Other ready-to-use main bodies (replace the body above; pair each with the matching gen main).
   Input for all of them: "n m" then m lines "u v" (add " w" for weighted ones).

    // MST weight (gen: connectedGraph + weights)
    int n, m; cin >> n >> m;
    vector<pii> e(m); vi w(m);
    for (int i = 0; i < m; i++) cin >> e[i].first >> e[i].second >> w[i];
    cout << mstWeight(n, e, w) << '\n';

    // max matching on a bipartite graph (gen: randBipartite, print n1+n2 as n)
    int n, m; cin >> n >> m;
    vector<pii> e(m);
    for (auto& [a, b] : e) cin >> a >> b;
    cout << maxMatching(n, e) << '\n';

    // SCC ids (gen: randDirected) and DAG check
    int n, m; cin >> n >> m;
    vector<pii> e(m); vi w(m);
    for (int i = 0; i < m; i++) cin >> e[i].first >> e[i].second >> w[i];
    vi c = sccMinNode(n, e);
    for (int i = 1; i <= n; i++) cout << c[i] << ' ';
    cout << isDAG(n, e) << '\n';

    // 2-SAT (gen: rand2SAT; clauses read as signed literals)
    int n, m; cin >> n >> m;
    vector<pii> c(m);
    for (auto& [a, b] : c) cin >> a >> b;
    cout << sat2(n, c) << '\n';
*/

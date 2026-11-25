#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Nodes are 1..n, a tree is a vector<pii> of n-1 edges. Weights are a parallel vi w, w[i] for e[i] (empty = all 1).
// Rooted functions use par[] / dep[] from parentDepth (par[root] = 0). Fine for n <= 100 unless noted.

// ---- adjacency ----
// g[u] = list of (neighbour, edge weight); weight 1 if w is empty.
vector<vector<pii>> adj(int n, const vector<pii>& e, const vi& w = {}) {
    vector<vector<pii>> g(n + 1);
    for (size_t i = 0; i < e.size(); i++) {
        int c = w.empty() ? 1 : w[i];
        g[e[i].first].push_back({e[i].second, c});
        g[e[i].second].push_back({e[i].first, c});
    }
    return g;
}

// ---- parent / depth ----
// Parent and depth (in edges) of every node when rooted at root; par[root] = 0. O(n).
pair<vi, vi> parentDepth(int n, const vector<pii>& e, int root = 1) {
    auto g = adj(n, e);
    vi par(n + 1, 0), dep(n + 1, 0);
    function<void(int, int)> go = [&](int v, int p) {
        par[v] = p;
        for (auto [u, c] : g[v]) if (u != p) dep[u] = dep[v] + 1, go(u, v);
    };
    go(root, 0);
    return {par, dep};
}

// ---- LCA ----
// Naive LCA: lift the deeper node, then lift both until equal. O(n) per query.
int naiveLCA(const vi& par, const vi& dep, int u, int v) {
    while (dep[u] > dep[v]) u = par[u];
    while (dep[v] > dep[u]) v = par[v];
    while (u != v) u = par[u], v = par[v];
    return u;
}

// ---- path vertices ----
// Vertices on the path u -> v, both ends included, in order. O(n).
vi pathVertices(const vi& par, const vi& dep, int u, int v) {
    int l = naiveLCA(par, dep, u, v);
    vi a, b;
    for (int x = u; x != l; x = par[x]) a.push_back(x);
    a.push_back(l);
    for (int x = v; x != l; x = par[x]) b.push_back(x);
    reverse(b.begin(), b.end());
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

// ---- k-th ancestor ----
// Walk up k times; returns 0 if it falls off the root. O(k).
int kthAncestor(const vi& par, int v, int k) {
    while (k-- && v) v = par[v];
    return v;
}

// ---- path sum / max edge ----
// {sum of edge weights, max edge weight} on the path u..v (DFS from u). u == v gives {0, 0}. O(n).
pair<ll, int> pathSumMax(int n, const vector<pii>& e, const vi& w, int u, int v) {
    auto g = adj(n, e, w);
    pair<ll, int> res = {0, 0};
    function<void(int, int, ll, int)> go = [&](int x, int p, ll s, int mx) {
        if (x == v) res = {s, mx};
        for (auto [y, c] : g[x]) if (y != p) go(y, x, s + c, max(mx, c));
    };
    go(u, 0, 0, 0);
    return res;
}

// ---- all-pairs distance ----
// d[i][j] = weighted distance, by a DFS from every node. O(n^2).
vector<vector<ll>> distAll(int n, const vector<pii>& e, const vi& w = {}) {
    auto g = adj(n, e, w);
    vector<vector<ll>> d(n + 1, vector<ll>(n + 1, 0));
    for (int s = 1; s <= n; s++) {
        function<void(int, int)> go = [&](int v, int p) {
            for (auto [u, c] : g[v]) if (u != p) d[s][u] = d[s][v] + c, go(u, v);
        };
        go(s, 0);
    }
    return d;
}

// ---- diameter ----
// Longest weighted path length = max over all pairs. O(n^2).
ll diameter(int n, const vector<pii>& e, const vi& w = {}) {
    auto d = distAll(n, e, w);
    ll best = 0;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) best = max(best, d[i][j]);
    return best;
}

// ---- sum of distances from every node ----
// s[v] = sum over u of dist(v, u) (what rerooting computes). O(n^2).
vector<ll> sumDist(int n, const vector<pii>& e, const vi& w = {}) {
    auto d = distAll(n, e, w);
    vector<ll> s(n + 1, 0);
    for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) s[i] += d[i][j];
    return s;
}

// ---- subtrees ----
// Subtree sizes for the tree rooted where par/dep came from: every node adds 1 to each of its ancestors. O(n * depth).
vi subtreeSizes(const vi& par) {
    int n = par.size() - 1;
    vi s(n + 1, 0);
    for (int v = 1; v <= n; v++) for (int x = v; x; x = par[x]) s[x]++;
    return s;
}
// Nodes in the subtree of v (v included), ascending. O(n * depth).
vi subtreeNodes(const vi& par, int v) {
    int n = par.size() - 1;
    vi r;
    for (int u = 1; u <= n; u++) {
        int x = u;
        while (x && x != v) x = par[x];
        if (x == v) r.push_back(u);
    }
    return r;
}

// ---- centroids ----
// All centroids (1 or 2): nodes whose removal leaves only components of size <= n/2. O(n^2).
vi centroids(int n, const vector<pii>& e) {
    auto g = adj(n, e);
    function<int(int, int)> cnt = [&](int v, int p) {
        int s = 1;
        for (auto [u, c] : g[v]) if (u != p) s += cnt(u, v);
        return s;
    };
    vi r;
    for (int v = 1; v <= n; v++) {
        int mx = 0;
        for (auto [u, c] : g[v]) mx = max(mx, cnt(u, v));
        if (2 * mx <= n) r.push_back(v);
    }
    return r;
}

// ---- extra: sums on node values ----
// val[1..n] are node values (1-indexed). Sum of val over the subtree of v when rooted at root. O(n * depth)
ll subtreeSum(int n, const vector<pii>& e, int root, const vi& val, int v) {
    ll s = 0;
    for (int u : subtreeNodes(parentDepth(n, e, root).first, v)) s += val[u];
    return s;
}
// Sum of val over all vertices on the path u..v (both ends included, u == v gives val[u]). O(n)
ll pathSum(int n, const vector<pii>& e, const vi& val, int u, int v) {
    auto [par, dep] = parentDepth(n, e, 1);
    ll s = 0;
    for (int x : pathVertices(par, dep, u, v)) s += val[x];
    return s;
}

int main() {
    // reads what gen.cpp prints: n, then n-1 lines "u v w"; prints the weighted diameter
    int n;
    cin >> n;
    vector<pii> e(n - 1);
    vi w(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> e[i].first >> e[i].second >> w[i];
    cout << diameter(n, e, w) << '\n';
}

/* Other ready-to-use main bodies (replace the body above; input is "n" then n-1 lines "u v" [w]):

    // LCA of two nodes (rooted at 1); add "u v" to the end of the input yourself
    int n, u, v; cin >> n;
    vector<pii> e(n - 1);
    for (auto& [a, b] : e) cin >> a >> b;
    cin >> u >> v;
    auto [par, dep] = parentDepth(n, e, 1);
    cout << naiveLCA(par, dep, u, v) << '\n';

    // centroids and subtree sizes
    int n; cin >> n;
    vector<pii> e(n - 1);
    for (auto& [a, b] : e) cin >> a >> b;
    for (int c : centroids(n, e)) cout << c << ' ';
    cout << '\n';
    for (int s : subtreeSizes(parentDepth(n, e, 1).first)) cout << s << ' ';
    cout << '\n';

    // sum of distances from every node (weighted)
    int n; cin >> n;
    vector<pii> e(n - 1); vi w(n - 1);
    for (int i = 0; i < n - 1; i++) cin >> e[i].first >> e[i].second >> w[i];
    vector<ll> s = sumDist(n, e, w);
    for (int i = 1; i <= n; i++) cout << s[i] << ' ';
    cout << '\n';

    // node values + path queries; input as the gen.cpp path-query example: n, edges "u v", values, q, then q lines "u v"
    int n, q; cin >> n;
    vector<pii> e(n - 1);
    for (auto& [a, b] : e) cin >> a >> b;
    vi val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];
    cin >> q;
    while (q--) { int u, v; cin >> u >> v; cout << pathSum(n, e, val, u, v) << '\n'; }

    // node values + subtree ops (here "1 v x" = a[v] += x; "2 v" = subtree sum, rooted at 1); input as the gen.cpp subtree example
    int n, q; cin >> n;
    vector<pii> e(n - 1);
    for (auto& [a, b] : e) cin >> a >> b;
    vi val(n + 1);
    for (int i = 1; i <= n; i++) cin >> val[i];
    cin >> q;
    while (q--) {
        int t, v, x; cin >> t >> v;
        if (t == 1) cin >> x, val[v] += x;
        else cout << subtreeSum(n, e, 1, val, v) << '\n';
    }
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Usage: ./gen SEED   (same seed -> same test, so a failing test can be rerun). No SEED -> random test.
mt19937_64 rng;

ll rnd(ll lo, ll hi) { return lo + rng() % (hi - lo + 1); } // [lo, hi]
bool randBool() { return rng() & 1; }
double randDouble(double lo, double hi) { return uniform_real_distribution<double>(lo, hi)(rng); }
template<class T> void shuf(vector<T>& v) { shuffle(v.begin(), v.end(), rng); }

vi randVec(int n, int lo, int hi) {
    vi v(n);
    for (int& x : v) x = rnd(lo, hi);
    return v;
}

vi randPerm(int n) { // 1..n
    vi p(n);
    iota(p.begin(), p.end(), 1);
    shuf(p);
    return p;
}

string randStr(int n, char lo = 'a', char hi = 'b') { // small alphabet finds more bugs
    string s(n, ' ');
    for (char& c : s) c = rnd(lo, hi);
    return s;
}

// ===== TREES =====
// Nodes are 1..n, a tree is a vector<pii> of n-1 edges. Weights (if any) are a parallel vi w, w[i] for e[i].

// ---- randTree ----
// KACTL genTree.h: uniform random tree from a Prufer code. Nodes 1..n, n-1 edges.
vector<pii> randTree(int n) {
    if (n == 1) return {};
    vi code(n - 2), deg(n + 1, 1);
    for (int& x : code) x = rnd(1, n), deg[x]++;
    set<int> leaves;
    for (int i = 1; i <= n; i++) if (deg[i] == 1) leaves.insert(i);
    vector<pii> e;
    for (int x : code) {
        int l = *leaves.begin();
        leaves.erase(l);
        e.push_back({l, x});
        if (--deg[x] == 1) leaves.insert(x);
    }
    e.push_back({*leaves.begin(), *leaves.rbegin()});
    shuf(e);
    return e;
}

// ---- randParentTree ----
// Parent array par[1..n] (par[1] = 0, root 1): par[i] = rnd(max(1, i-k), i-1), so par[i] < i.
// k = 1 gives a path, small k gives deep trees, k >= n gives random recursive trees (shallow).
vi randParentTree(int n, int k = 1e9) {
    vi par(n + 1, 0);
    for (int i = 2; i <= n; i++) par[i] = rnd(max(1, i - k), i - 1);
    return par;
}

// ---- parentToEdges ----
// Edge list (par[i], i) for i = 2..n from a parent array.
vector<pii> parentToEdges(const vi& par) {
    vector<pii> e;
    for (int i = 2; i < (int)par.size(); i++) e.push_back({par[i], i});
    return e;
}

// ---- shapes ----
// Path 1-2-...-n.
vector<pii> pathTree(int n) {
    vector<pii> e;
    for (int i = 2; i <= n; i++) e.push_back({i - 1, i});
    return e;
}
// Star with center 1.
vector<pii> starTree(int n) {
    vector<pii> e;
    for (int i = 2; i <= n; i++) e.push_back({1, i});
    return e;
}
// Caterpillar: spine path 1..k (k random), every other node is a leaf on a random spine node.
vector<pii> caterpillar(int n) {
    int k = rnd(1, n);
    vector<pii> e = pathTree(k);
    for (int i = k + 1; i <= n; i++) e.push_back({(int)rnd(1, k), i});
    return e;
}
// Complete binary tree in heap order: parent of i is i/2 (root 1).
vector<pii> binaryTree(int n) {
    vector<pii> e;
    for (int i = 2; i <= n; i++) e.push_back({i / 2, i});
    return e;
}

// ---- relabel ----
// Randomly renames nodes, shuffles edge order, randomly flips edge directions. Use it on the shape trees above
// (and parentToEdges) so node 1 is not always the root/centre. Make weights AFTER it (w[i] must match e[i]).
vector<pii> relabel(vector<pii> e) {
    vi p = randPerm(e.size() + 1);
    for (auto& [a, b] : e) {
        a = p[a - 1], b = p[b - 1];
        if (randBool()) swap(a, b);
    }
    shuf(e);
    return e;
}

// ---- weights ----
// Weights: just use randVec(n - 1, lo, hi) (vi, w[i] for e[i]).

// ---- printTree ----
// Prints n, then n-1 lines "u v" (or "u v w" if w is given).
void printTree(int n, const vector<pii>& e, const vi& w = {}) {
    cout << n << '\n';
    for (size_t i = 0; i < e.size(); i++) {
        cout << e[i].first << ' ' << e[i].second;
        if (w.size()) cout << ' ' << w[i];
        cout << '\n';
    }
}

// ---- extra: queries and node values ----
vector<pii> pathQueries(int n, int q) { // q pairs (u, v), 1 <= u, v <= n, u == v allowed (LCA / HLD path queries)
    vector<pii> r(q);
    for (pii& p : r) p = {(int)rnd(1, n), (int)rnd(1, n)};
    return r;
}

vi nodeValues(int n, int lo, int hi) { // 1-indexed a[1..n] (a[0] = 0 unused), values in [lo, hi]
    vi a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = rnd(lo, hi);
    return a;
}

// q ops as {t, v, x} for Euler-tour problems. t=1: "1 v x" update (add x to the subtree of v, or set a[v] = x: your problem decides), x in [lo, hi].
// t=2: "2 v" subtree-sum query (x = 0, don't print it). v in [1, n]
vector<array<int, 3>> subtreeQueries(int n, int q, int lo, int hi) {
    vector<array<int, 3>> r;
    while (q--) {
        if (randBool()) r.push_back({1, (int)rnd(1, n), (int)rnd(lo, hi)});
        else r.push_back({2, (int)rnd(1, n), 0});
    }
    return r;
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());

    // uniform random weighted tree
    int n = rnd(1, 8);
    printTree(n, randTree(n), randVec(n - 1, 1, 9));

    /* Other ready-to-use main bodies (replace the body above):

    // deep-ish tree from a parent array, relabelled (k = 2: each parent is one of the last 2 nodes)
    int n = rnd(1, 8);
    printTree(n, relabel(parentToEdges(randParentTree(n, 2))));

    // special shapes, relabelled
    int n = rnd(1, 8);
    vector<pii> e = pathTree(n);   // or starTree(n), caterpillar(n), binaryTree(n)
    printTree(n, relabel(e));

    // rooted tree printed as the parent list "p2 p3 ... pn" (root 1, par[i] < i)
    int n = rnd(1, 8);
    vi par = randParentTree(n);
    cout << n << '\n';
    for (int i = 2; i <= n; i++) cout << par[i] << ' ';
    cout << '\n';

    // node values + path queries (LCA / HLD): n, n-1 edges, values a1..an, q, then q lines "u v"
    int n = rnd(1, 8), q = rnd(1, 8);
    printTree(n, randTree(n));
    vi a = nodeValues(n, -5, 5);
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << '\n' << q << '\n';
    for (pii p : pathQueries(n, q)) cout << p.first << ' ' << p.second << '\n';

    // node values + subtree ops (Euler tour): n, n-1 edges, values a1..an, q, then q lines "1 v x" or "2 v"
    int n = rnd(1, 8), q = rnd(1, 8);
    printTree(n, randTree(n));
    vi a = nodeValues(n, -5, 5);
    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << '\n' << q << '\n';
    for (auto& o : subtreeQueries(n, q, -5, 5)) {
        cout << o[0] << ' ' << o[1];
        if (o[0] == 1) cout << ' ' << o[2];
        cout << '\n';
    }
    */
}

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

// ===== GRAPH =====
// Nodes are 1..n. Edge lists are vector<pii>. Weights (if any) are a parallel vi w, w[i] belongs to e[i].

// ---- randGraph ----
// Simple undirected graph (no loops/multi-edges), m <= n(n-1)/2. May be disconnected.
vector<pii> randGraph(int n, int m) {
    assert(m <= (ll)n * (n - 1) / 2);
    set<pii> seen;
    vector<pii> e;
    while ((int)e.size() < m) {
        int a = rnd(1, n), b = rnd(1, n);
        if (a == b || !seen.insert(minmax(a, b)).second) continue;
        if (randBool()) swap(a, b);
        e.push_back({a, b});
    }
    return e;
}

// ---- connectedGraph ----
// Simple connected undirected graph: random spanning tree + extra edges. n-1 <= m <= n(n-1)/2.
vector<pii> connectedGraph(int n, int m) {
    assert(m >= n - 1 && m <= (ll)n * (n - 1) / 2);
    set<pii> seen;
    vector<pii> e;
    auto add = [&](int a, int b) {
        if (a != b && seen.insert(minmax(a, b)).second) e.push_back({a, b});
    };
    vi p = randPerm(n);
    for (int i = 1; i < n; i++) add(p[rnd(0, i - 1)], p[i]);
    while ((int)e.size() < m) add(rnd(1, n), rnd(1, n));
    shuf(e);
    return e;
}

// ---- randDirected ----
// Directed edges u->v: no self loops, no duplicate (u,v). u->v and v->u may both appear. m <= n(n-1).
vector<pii> randDirected(int n, int m) {
    assert(m <= (ll)n * (n - 1));
    set<pii> seen;
    vector<pii> e;
    while ((int)e.size() < m) {
        int a = rnd(1, n), b = rnd(1, n);
        if (a != b && seen.insert({a, b}).second) e.push_back({a, b});
    }
    return e;
}

// ---- randDAG ----
// Acyclic directed edges u->v, no duplicates. Hidden random topological order. m <= n(n-1)/2.
vector<pii> randDAG(int n, int m) {
    assert(m <= (ll)n * (n - 1) / 2);
    vi p = randPerm(n); // p[0], p[1], ... is a topological order
    set<pii> seen;
    vector<pii> e;
    while ((int)e.size() < m) {
        int a = rnd(0, n - 1), b = rnd(0, n - 1);
        if (a < b && seen.insert({a, b}).second) e.push_back({p[a], p[b]});
    }
    return e;
}

// ---- randBipartite ----
// Left side 1..n1, right side n1+1..n1+n2; edges (left, right), no duplicates. m <= n1*n2.
vector<pii> randBipartite(int n1, int n2, int m) {
    assert(m <= (ll)n1 * n2);
    set<pii> seen;
    vector<pii> e;
    while ((int)e.size() < m) {
        int a = rnd(1, n1), b = rnd(n1 + 1, n1 + n2);
        if (seen.insert({a, b}).second) e.push_back({a, b});
    }
    return e;
}

// ---- randFunctional ----
// Functional graph: every node i has exactly one edge i->f(i). n edges; self loops allowed.
vector<pii> randFunctional(int n) {
    vector<pii> e;
    for (int i = 1; i <= n; i++) e.push_back({i, (int)rnd(1, n)});
    return e;
}

// ---- completeGraph ----
// All n(n-1)/2 undirected edges (i, j), i < j.
vector<pii> completeGraph(int n) {
    vector<pii> e;
    for (int i = 1; i <= n; i++) for (int j = i + 1; j <= n; j++) e.push_back({i, j});
    return e;
}

// ---- rand2SAT ----
// m clauses (a or b) over variables 1..n. Literal +x = x, -x = not x. Two different variables per clause.
vector<pii> rand2SAT(int n, int m) {
    assert(n >= 2);
    vector<pii> c;
    while ((int)c.size() < m) {
        int a = rnd(1, n), b = rnd(1, n);
        if (a == b) continue;
        c.push_back({randBool() ? a : -a, randBool() ? b : -b});
    }
    return c;
}

// ---- weights ----
// Weights: just use randVec(sz(e), lo, hi) (vi, w[i] for e[i]).

// ---- printGraph ----
// Prints "n m" then one edge per line "u v" (or "u v w" if w is given).
void printGraph(int n, const vector<pii>& e, const vi& w = {}) {
    cout << n << ' ' << e.size() << '\n';
    for (size_t i = 0; i < e.size(); i++) {
        cout << e[i].first << ' ' << e[i].second;
        if (w.size()) cout << ' ' << w[i];
        cout << '\n';
    }
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());

    // weighted directed graph (shortest paths, SCC, ...)
    int n = rnd(1, 6), m = rnd(0, n * (n - 1));
    printGraph(n, randDirected(n, m), randVec(m, 1, 9));

    /* Other ready-to-use main bodies (replace the body above):

    // connected undirected graph with weights (MST, bridges, ...)
    int n = rnd(1, 7), m = rnd(n - 1, n * (n - 1) / 2);
    printGraph(n, connectedGraph(n, m), randVec(m, 1, 9));

    // DAG
    int n = rnd(1, 7), m = rnd(0, n * (n - 1) / 2);
    printGraph(n, randDAG(n, m));

    // bipartite graph (matching): n = n1 + n2 nodes
    int n1 = rnd(1, 5), n2 = rnd(1, 5), m = rnd(0, n1 * n2);
    printGraph(n1 + n2, randBipartite(n1, n2, m));

    // 2-SAT: n variables, m clauses
    int n = rnd(2, 6), m = rnd(1, 10);
    printGraph(n, rand2SAT(n, m));
    */
}

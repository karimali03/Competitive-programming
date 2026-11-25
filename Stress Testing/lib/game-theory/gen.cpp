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

// ===== GAME THEORY =====
// Keep everything SMALL: the brute explores every reachable state.

// ---- randPiles ----
// k piles, each in [0, maxV]. Use maxV <= 6 and k <= 4 for the full-recursion brutes.
vi randPiles(int k, int maxV) { return randVec(k, 0, maxV); }

// ---- randMoveSet ----
// k distinct allowed "take" amounts from [1, maxT], sorted (subtraction game). k <= maxT.
vi randMoveSet(int k, int maxT) {
    vi p = randPerm(maxT);
    vi s(p.begin(), p.begin() + k);
    sort(s.begin(), s.end());
    return s;
}

// ---- randDAG ----
// Game graph: token moves along u->v, no cycles, no duplicates. Nodes 1..n, m <= n(n-1)/2.
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

// ---- randGameArray ----
// Array for "take from the left or right end" games. Small n (<= 18 for plain recursion).
vi randGameArray(int n, int lo, int hi) { return randVec(n, lo, hi); }

// ---- classic games ----
// Parents for a random rooted tree: node 0 is the root/ground, par[v] in [0, v-1] for v >= 1 (par[0] = 0, unused). n nodes = n-1 edges.
vi randTreeParents(int n) {
    vi par(n, 0);
    for (int v = 1; v < n; v++) par[v] = rnd(0, v - 1);
    return par;
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());

    // Subtraction game: "n k" then the k allowed take amounts.
    int k = rnd(1, 3);
    vi S = randMoveSet(k, 5);
    cout << rnd(0, 30) << ' ' << k << '\n';
    for (int x : S) cout << x << ' ';
    cout << '\n';
}

/* Other ready-to-use main bodies (pair each with the matching brute main):

    // Wythoff (also Euclid): "a b"
    int a = rnd(0, 20), b = rnd(0, 20);
    cout << a << ' ' << b << '\n';

    // Chomp: "r c"
    cout << rnd(1, 5) << ' ' << rnd(1, 5) << '\n';

    // Hackenbush tree: "n" then the parents of nodes 1..n-1
    int n = rnd(1, 11);
    cout << n << '\n';
    vi par = randTreeParents(n);
    for (int v = 1; v < n; v++) cout << par[v] << ' ';
    cout << '\n';

    // Nim piles: "k" then k piles
    int k = rnd(1, 4);
    cout << k << '\n';
    for (int x : randPiles(k, 5)) cout << x << ' ';
    cout << '\n';

    // Token on a DAG: "n m start" then m lines "u v"
    int n = rnd(1, 8), m = rnd(0, n * (n - 1) / 2);
    cout << n << ' ' << m << ' ' << rnd(1, n) << '\n';
    for (auto [u, v] : randDAG(n, m)) cout << u << ' ' << v << '\n';

    // Take-from-ends array: "n" then n values
    int n = rnd(1, 10);
    cout << n << '\n';
    for (int x : randGameArray(n, 1, 10)) cout << x << ' ';
    cout << '\n';
*/

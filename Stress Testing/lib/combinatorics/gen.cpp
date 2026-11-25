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

// ===== COMBINATORICS =====
// Keep n tiny: the brutes enumerate permutations / subsets / set partitions (n <= ~9).

// ---- randPrime ----
// A random prime modulus: the usual big ones (formulas) or a tiny prime (tests Lucas / p <= n edge cases).
ll randPrime() {
    ll P[] = {1000000007, 998244353, 2, 3, 5, 7, 11, 13};
    return P[rnd(0, 7)];
}

// ---- randNK ----
// n in [0, maxN], k in [0, n] (k <= n, so binom-like answers are non-trivial).
pii randNK(int maxN) {
    int n = rnd(0, maxN);
    return {n, (int)rnd(0, n)};
}

// ---- randMultiset ----
// String of n letters from the first `alpha` letters, so letters repeat (use for multiset permutations / necklaces).
string randMultiset(int n, int alpha) { return randStr(n, 'a', 'a' + alpha - 1); }

// ---- randGrid ----
// r x c grid, '#' blocked with probability pct%, top-left and bottom-right always '.'.
vector<string> randGrid(int r, int c, int pct) {
    vector<string> g(r, string(c, '.'));
    for (auto& row : g) for (char& ch : row) if (rnd(1, 100) <= pct) ch = '#';
    g[0][0] = g[r - 1][c - 1] = '.';
    return g;
}

// ---- printGrid ----
// Prints "r c" then the rows.
void printGrid(const vector<string>& g) {
    cout << g.size() << ' ' << g[0].size() << '\n';
    for (auto& row : g) cout << row << '\n';
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());

    // "n k p": n choose k mod p (also n, k for Catalan / derangements / Stirling / ...)
    auto [n, k] = randNK(12);
    cout << n << ' ' << k << ' ' << randPrime() << '\n';

    /* Other ready-to-use main bodies (replace the body above; pair each with the matching brute main):

    // "n k": partitions, set partitions, compositions, necklaces, surjections, inversions
    int n = rnd(0, 7), k = rnd(0, 4);
    cout << n << ' ' << k << '\n';

    // multiset string: distinct arrangements
    cout << randMultiset(rnd(1, 8), rnd(1, 3)) << '\n';

    // grid with blocked cells: lattice paths (right/down)
    printGrid(randGrid(rnd(1, 6), rnd(1, 6), 25));
    */
}

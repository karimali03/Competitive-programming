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

// ===== VARIOUS (DP / knapsack / LIS / small exhaustive problems) =====

vi randSeq(int n, int k) { // 0-indexed seq of n values in [1, k]; small k gives many duplicates (LIS / LCS)
    return randVec(n, 1, k);
}

vector<pii> randItems(int n, int maxW, int maxV) { // n items (weight, value), weight in [1, maxW], value in [1, maxV]
    vector<pii> it(n);
    for (pii& p : it) p = {rnd(1, maxW), rnd(1, maxV)};
    return it;
}

vi randCoins(int k, int maxC) { // k distinct coin values in [1, maxC], sorted increasing (needs k <= maxC)
    vi p = randPerm(maxC);
    p.resize(k);
    sort(p.begin(), p.end());
    return p;
}

vector<array<int, 3>> randJobs(int n, int maxT, int maxW) { // n jobs (l, r, w), half-open [l, r) with 0 <= l < r <= maxT (maxT >= 1), weight in [1, maxW]
    vector<array<int, 3>> v(n);
    for (auto& j : v) {
        int l = rnd(0, maxT - 1);
        j = {l, (int)rnd(l + 1, maxT), (int)rnd(1, maxW)};
    }
    return v;
}

vector<vi> randDistMat(int n, int maxW, bool sym) { // 0-indexed n x n distance matrix for TSP: d[i][i] = 0, d[i][j] in [1, maxW], symmetric if sym
    vector<vi> d(n, vi(n));
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) if (i != j) {
        d[i][j] = (sym && j < i) ? d[j][i] : rnd(1, maxW);
    }
    return d;
}

vector<string> randObsGrid(int R, int C, int pct) { // 0-indexed R rows of C chars: '#' obstacle with probability pct%, else '.'. Corners (0,0) and (R-1,C-1) are always '.'
    vector<string> g(R, string(C, '.'));
    for (string& row : g) for (char& c : row) if (rnd(1, 100) <= pct) c = '#';
    g[0][0] = g[R - 1][C - 1] = '.';
    return g;
}

// ---- extra: partitions, distinct values, sorted arrays ----
vi randPartition(int n, int k) { // k POSITIVE ints summing to n (1 <= k <= n, n up to ~1e6): stars and bars, k-1 distinct cut points in 1..n-1
    vi c = randPerm(n - 1);
    c.resize(k - 1);
    c.push_back(0), c.push_back(n);
    sort(c.begin(), c.end());
    vi r(k);
    for (int i = 0; i < k; i++) r[i] = c[i + 1] - c[i];
    return r;
}

vi randPartition0(int n, int k) { // k NON-NEGATIVE ints summing to n (k >= 1; needs randPartition): partition n+k into k positive parts, subtract 1 from each
    vi r = randPartition(n + k, k);
    for (int& x : r) x--;
    return r;
}

vector<ll> randDistinct(int n, ll lo, ll hi) { // n distinct values in [lo, hi] in random order (hi-lo+1 >= n). Rejection with a set: fine for huge ranges (1e18), slow only if n is close to hi-lo+1 (then use randPerm)
    set<ll> seen;
    vector<ll> v;
    while ((int)v.size() < n) {
        ll x = rnd(lo, hi);
        if (seen.insert(x).second) v.push_back(x);
    }
    return v;
}

vector<ll> randSorted(int n, ll lo, ll hi, bool strict) { // sorted increasing array of n values in [lo, hi]; strict = no duplicates (needs randDistinct, hi-lo+1 >= n)
    vector<ll> v;
    if (strict) v = randDistinct(n, lo, hi);
    else while ((int)v.size() < n) v.push_back(rnd(lo, hi));
    sort(v.begin(), v.end());
    return v;
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    // one test: items (weight value) + capacity W. Brute treats it as knapsack, subset sum / coin change on the weights, and LIS on the values
    int n = rnd(1, 7), W = rnd(1, 15);
    auto it = randItems(n, 6, 4);
    printf("%d %d\n", n, W);
    for (pii p : it) printf("%d %d\n", p.first, p.second);
}

/* Other main bodies (paste inside main after the rng.seed line; matching brute mains are at the bottom of brute.cpp):

// two strings (LCS / edit distance)
printf("%s\n%s\n", randStr(rnd(1, 7)).c_str(), randStr(rnd(1, 7)).c_str());

// TSP
int n = rnd(1, 6);
auto d = randDistMat(n, 9, randBool());
printf("%d\n", n);
for (int i = 0; i < n; i++, puts("")) for (int j = 0; j < n; j++) printf("%d ", d[i][j]);

// weighted interval scheduling
int n = rnd(1, 8);
auto jobs = randJobs(n, 10, 9);
printf("%d\n", n);
for (auto& j : jobs) printf("%d %d %d\n", j[0], j[1], j[2]);

// grid path counting (obstacles)
int R = rnd(1, 6), C = rnd(1, 6);
auto g = randObsGrid(R, C, 25);
printf("%d %d\n", R, C);
for (string& row : g) puts(row.c_str());

// array of small values / bitmasks (max subarray, inversions, subset xor)
int n = rnd(1, 8);
vi a = randVec(n, -5, 5); // bitmasks: randVec(n, 0, (1 << bits) - 1)
printf("%d\n", n);
for (int x : a) printf("%d ", x);
puts("");

// partition of n into k positive parts (ints; use randPartition0 for non-negative)
int n = rnd(1, 10), k = rnd(1, n);
vi p = randPartition(n, k);
printf("%d %d\n", n, k);
for (int x : p) printf("%d ", x);
puts("");

// sorted array, strictly increasing half of the time (binary search / two pointers / counting pairs)
int n = rnd(1, 8);
auto a = randSorted(n, 1, 20, randBool());
printf("%d\n", n);
for (ll x : a) printf("%lld ", x);
puts("");
*/

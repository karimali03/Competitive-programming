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

// ===== DATA STRUCTURES =====

// ---- arrays ----
vi randArr(int n, int lo, int hi) { // 1-indexed a[1..n] (a[0]=0 unused), values in [lo, hi]
    vi a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = rnd(lo, hi);
    return a;
}

vi edgeArr(int n, int mode, int lo, int hi) { // 1-indexed. mode 0: all equal, 1: increasing, 2: decreasing, 3: random
    vi a = randArr(n, lo, hi);
    if (mode == 0) fill(a.begin() + 1, a.end(), a[1]);
    if (mode == 1) sort(a.begin() + 1, a.end());
    if (mode == 2) sort(a.begin() + 1, a.end(), greater<int>());
    return a;
}

// ---- ranges and queries ----
pii randRange(int n) { // [l, r] with 1 <= l <= r <= n
    int l = rnd(1, n), r = rnd(1, n);
    return {min(l, r), max(l, r)};
}

// q ops as {t, a, b, c}. t=1: "1 i x" point update (a=i, b=x, c=0). t=2: "2 l r" range query (a=l, b=r, c=0). i, l, r in [1, n], x in [lo, hi]
vector<array<int, 4>> pointOps(int n, int q, int lo, int hi) {
    vector<array<int, 4>> ops;
    while (q--) {
        if (randBool()) ops.push_back({1, (int)rnd(1, n), (int)rnd(lo, hi), 0});
        else { pii r = randRange(n); ops.push_back({2, r.first, r.second, 0}); }
    }
    return ops;
}

// q ops as {t, a, b, c}. t=1: "1 l r x" range update (a=l, b=r, c=x). t=2: "2 l r" range query (a=l, b=r, c=0). 1 <= l <= r <= n, x in [lo, hi]
vector<array<int, 4>> rangeOps(int n, int q, int lo, int hi) {
    vector<array<int, 4>> ops;
    while (q--) {
        pii r = randRange(n);
        if (randBool()) ops.push_back({1, r.first, r.second, (int)rnd(lo, hi)});
        else ops.push_back({2, r.first, r.second, 0});
    }
    return ops;
}

// ---- 2D grid ----
vector<vi> randGrid(int R, int C, int lo, int hi) { // 1-indexed g[1..R][1..C] (row/col 0 unused), values in [lo, hi]
    vector<vi> g(R + 1, vi(C + 1));
    for (int i = 1; i <= R; i++) for (int j = 1; j <= C; j++) g[i][j] = rnd(lo, hi);
    return g;
}

array<int, 4> randRect(int R, int C) { // {r1, c1, r2, c2} with 1 <= r1 <= r2 <= R, 1 <= c1 <= c2 <= C
    pii r = randRange(R), c = randRange(C);
    return {r.first, c.first, r.second, c.second};
}

// ---- lines (convex hull trick / LineContainer) ----
vector<pair<ll, ll>> randLines(int n, int lo, int hi) { // n lines (k, m) meaning y = k*x + m, k and m in [lo, hi]
    vector<pair<ll, ll>> v(n);
    for (auto& p : v) p = {rnd(lo, hi), rnd(lo, hi)};
    return v;
}

// ---- intervals ----
vector<pii> randIntervals(int n, int maxC) { // n intervals (l, r) with 1 <= l <= r <= maxC (use as half-open [l, r) if wanted)
    vector<pii> v(n);
    for (pii& p : v) p = randRange(maxC);
    return v;
}

// ---- set / multiset operations ----
// q ops as {t, x}. t=1: insert x. t=2: erase one copy of x (no-op if absent). t=3: k-th smallest (x=k, 1 <= k <= size, only when nonempty). t=4: count elements < x. x in [1, maxV]
vector<pii> setOps(int q, int maxV) {
    vector<pii> ops;
    multiset<int> s;
    while (q--) {
        int t = rnd(1, 4);
        if (t == 3 && s.empty()) t = 1;
        if (t == 1) { int x = rnd(1, maxV); ops.push_back({1, x}); s.insert(x); }
        if (t == 2) { int x = rnd(1, maxV); ops.push_back({2, x}); auto it = s.find(x); if (it != s.end()) s.erase(it); }
        if (t == 3) ops.push_back({3, (int)rnd(1, s.size())});
        if (t == 4) ops.push_back({4, (int)rnd(1, maxV)});
    }
    return ops;
}

// ---- extra: anti unordered_map ----
// n distinct keys, all multiples of the prime p (default 172933). With GCC's unordered_map<ll,...> the hash is the key itself, bucket = key % bucket_count, and the
// bucket count grows through ..., 42043, 85229, 172933, 351061, ... So with n >= 85230 keys, while the table has 172933 buckets every key lands in ONE bucket and
// each insert/find walks a chain of ~1e5 nodes: O(n) per op. Use it to TLE-test a solution that uses unordered_map<ll,int>. (n = 2e5 is ~100x+ slower than random keys.)
// Keys reach n*p (~3.5e10), so it only applies to problems with 64-bit keys. p = 351061 hits the next size; 107897 / 126271 (often quoted) do nothing on GCC 14.
// Fix in the solution: a custom hash, e.g. splitmix64(x + SEED) with SEED from chrono::steady_clock, passed as the 3rd template argument.
vector<ll> antiUnorderedMap(int n, ll p = 172933) {
    vector<ll> k(n);
    for (int i = 0; i < n; i++) k[i] = (ll)(i + 1) * p;
    return k;
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    // one test: array + mixed range-add / range-query ops
    int n = rnd(1, 8), q = rnd(1, 8);
    vi a = randArr(n, -5, 5);
    auto ops = rangeOps(n, q, -5, 5);
    printf("%d %d\n", n, q);
    for (int i = 1; i <= n; i++) printf("%d ", a[i]);
    puts("");
    for (auto& o : ops) printf("%d %d %d %d\n", o[0], o[1], o[2], o[3]);
}

/* Other main bodies (paste inside main after the rng.seed line):

// point-update / range-query ops
int n = rnd(1, 8), q = rnd(1, 8);
vi a = randArr(n, 0, 3);
auto ops = pointOps(n, q, 0, 3);
printf("%d %d\n", n, q);
for (int i = 1; i <= n; i++) printf("%d ", a[i]);
puts("");
for (auto& o : ops) printf("%d %d %d\n", o[0], o[1], o[2]);

// 2D grid + rectangle queries
int R = rnd(1, 5), C = rnd(1, 5), q = rnd(1, 5);
auto g = randGrid(R, C, -5, 5);
printf("%d %d %d\n", R, C, q);
for (int i = 1; i <= R; i++, puts("")) for (int j = 1; j <= C; j++) printf("%d ", g[i][j]);
while (q--) { auto r = randRect(R, C); printf("%d %d %d %d\n", r[0], r[1], r[2], r[3]); }

// lines (k, m) + query points
int n = rnd(1, 6), q = rnd(1, 6);
auto L = randLines(n, -5, 5);
printf("%d %d\n", n, q);
for (auto& p : L) printf("%lld %lld\n", p.first, p.second);
while (q--) printf("%d\n", (int)rnd(-5, 5));

// multiset ops
int q = rnd(1, 10);
auto ops = setOps(q, 5);
printf("%d\n", q);
for (auto& o : ops) printf("%d %d\n", o.first, o.second);

// sorted edge-case array (mode 0 equal / 1 increasing / 2 decreasing / 3 random)
int n = rnd(1, 8);
vi a = edgeArr(n, rnd(0, 3), 1, 5);
printf("%d\n", n);
for (int i = 1; i <= n; i++) printf("%d ", a[i]);
puts("");

// anti unordered_map: n keys, one per line (n >= 85230 to trigger it; then run your solution on it to check for TLE)
int n = 2e5;
printf("%d\n", n);
for (ll x : antiUnorderedMap(n)) printf("%lld\n", x);
*/

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

// ===== GEOMETRY =====
// Integer coordinates only. Small lim (like 2..5) gives many collinear/duplicate points = finds bugs.
struct P { ll x, y; };
bool operator<(P a, P b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }
bool operator==(P a, P b) { return a.x == b.x && a.y == b.y; }
ll cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); }

P randPoint(ll lim) { return {rnd(-lim, lim), rnd(-lim, lim)}; } // x,y in [-lim, lim]

vector<P> randPoints(int n, ll lim, bool distinct = false) { // n points in [-lim,lim]^2; distinct needs n <= (2lim+1)^2
    vector<P> v;
    set<P> seen;
    while ((int)v.size() < n) {
        P p = randPoint(lim);
        if (distinct && !seen.insert(p).second) continue;
        v.push_back(p);
    }
    return v;
}

vector<P> randCollinear(int n, ll lim) { // n points (duplicates possible) on one random line; coords in [-2lim, 2lim]
    P a = randPoint(lim), d = {0, 0};
    while (d.x == 0 && d.y == 0) d = {rnd(-1, 1), rnd(-1, 1)};
    vector<P> v;
    while (n--) { ll t = rnd(0, lim); v.push_back({a.x + t * d.x, a.y + t * d.y}); }
    return v;
}

pair<P, P> randSegment(ll lim) { // segment with distinct endpoints
    P a = randPoint(lim), b = randPoint(lim);
    while (a == b) b = randPoint(lim);
    return {a, b};
}

vector<P> randTriangle(ll lim) { // non-degenerate triangle, CCW
    P a, b, c;
    do a = randPoint(lim), b = randPoint(lim), c = randPoint(lim); while (cross(a, b, c) == 0);
    if (cross(a, b, c) < 0) swap(b, c);
    return {a, b, c};
}

vector<P> randSimplePolygon(int n, ll lim) { // simple polygon, CCW, n distinct vertices (n>=3, not all collinear), may have 180-degree vertices; star-shaped around a vertex
    assert(n >= 3 && (2 * lim + 1) * (2 * lim + 1) >= n);
    vector<P> v;
    do v = randPoints(n, lim, true); while (all_of(v.begin(), v.end(), [&](P p) { return cross(v[0], v[1], p) == 0; }));
    P o = *min_element(v.begin(), v.end(), [](P a, P b) { return make_pair(a.y, a.x) < make_pair(b.y, b.x); });
    v.erase(find(v.begin(), v.end(), o));
    sort(v.begin(), v.end(), [&](P a, P b) { // by angle around o, then by distance
        ll c = cross(o, a, b);
        if (c) return c > 0;
        return abs(a.x - o.x) + abs(a.y - o.y) < abs(b.x - o.x) + abs(b.y - o.y);
    });
    int k = n - 2; // last group of points on the same ray goes back in reverse order
    while (k > 0 && cross(o, v[k - 1], v.back()) == 0) k--;
    reverse(v.begin() + k, v.end());
    v.insert(v.begin(), o);
    rotate(v.begin(), v.begin() + rnd(0, n - 1), v.end());
    return v;
}

vector<P> randConvexPolygon(int n, ll lim) { // strictly convex polygon, CCW, 3..n vertices (hull of n random points; lim >= 1)
    assert(n >= 3 && lim >= 1);
    while (1) {
        vector<P> p = randPoints(n, lim), h(2 * n);
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        int m = p.size(), t = 0;
        if (m < 3) continue;
        for (int i = 0; i < m; h[t++] = p[i++]) while (t >= 2 && cross(h[t - 2], h[t - 1], p[i]) <= 0) t--;
        for (int i = m - 2, s = t + 1; i >= 0; h[t++] = p[i--]) while (t >= s && cross(h[t - 2], h[t - 1], p[i]) <= 0) t--;
        h.resize(t - 1);
        if (h.size() >= 3) return h;
    }
}

array<ll, 3> randCircle(ll lim, ll maxR) { // {x, y, r}: center in [-lim,lim]^2, radius in [1, maxR]
    P c = randPoint(lim);
    return {c.x, c.y, rnd(1, maxR)};
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    // Example: simple polygon (n, then n points CCW) and a query point.
    int n = rnd(3, 8);
    vector<P> poly = randSimplePolygon(n, 4);
    P q = randPoint(5);
    printf("%d\n", n);
    for (P p : poly) printf("%lld %lld\n", p.x, p.y);
    printf("%lld %lld\n", q.x, q.y);
}

/* Other main bodies (replace the one above; the matching brute.cpp mains are listed there):

// point set: n, then n points (closest/farthest pair, convex hull, min enclosing circle)
int n = rnd(2, 8);
vector<P> v = randPoints(n, 5);
printf("%d\n", n);
for (P p : v) printf("%lld %lld\n", p.x, p.y);

// two segments: a b c d (segment intersection)
auto s = randSegment(4), t = randSegment(4);
printf("%lld %lld %lld %lld\n", s.first.x, s.first.y, s.second.x, s.second.y);
printf("%lld %lld %lld %lld\n", t.first.x, t.first.y, t.second.x, t.second.y);

// convex polygon + query point (point in polygon)
int n = rnd(3, 10);
vector<P> poly = randConvexPolygon(n, 5);
P q = randPoint(6);
printf("%d\n", (int)poly.size());
for (P p : poly) printf("%lld %lld\n", p.x, p.y);
printf("%lld %lld\n", q.x, q.y);

// triangle (lattice points inside): a b c
auto t = randTriangle(6);
for (P p : t) printf("%lld %lld\n", p.x, p.y);
*/

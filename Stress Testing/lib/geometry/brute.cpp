#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Integer points, exact arithmetic (coords up to ~1e9 are safe in ll). No epsilons except the circle brute.
struct P { ll x, y; };
bool operator<(P a, P b) { return make_pair(a.x, a.y) < make_pair(b.x, b.y); }
bool operator==(P a, P b) { return a.x == b.x && a.y == b.y; }
ll cross(P o, P a, P b) { return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x); } // >0: o->a->b turns left
ll dot(P o, P a, P b) { return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y); }
int sgn(ll x) { return (x > 0) - (x < 0); }
ll dist2(P a, P b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); }

// ---- polygon area ----
// doubled signed area (shoelace), positive if CCW. O(n)
ll area2(const vector<P>& v) {
    ll s = 0;
    for (int i = 0; i < (int)v.size(); i++) s += cross(P{0, 0}, v[i], v[(i + 1) % v.size()]);
    return s;
}

// ---- point on segment ----
// p lies on segment ab (endpoints included; a==b allowed). O(1)
bool onSeg(P a, P b, P p) { return cross(a, b, p) == 0 && dot(p, a, b) <= 0; }

// ---- segments intersect ----
// segments ab and cd share at least one point (touching/collinear overlap counts). O(1)
bool segInter(P a, P b, P c, P d) {
    if (onSeg(a, b, c) || onSeg(a, b, d) || onSeg(c, d, a) || onSeg(c, d, b)) return true;
    return sgn(cross(a, b, c)) * sgn(cross(a, b, d)) < 0 && sgn(cross(c, d, a)) * sgn(cross(c, d, b)) < 0; // proper crossing
}

// ---- point in polygon ----
// 0 = outside, 1 = on boundary, 2 = strictly inside; any simple polygon, either orientation. O(n)
int inPoly(const vector<P>& v, P p) {
    int n = v.size(), in = 0;
    for (int i = 0; i < n; i++) {
        P a = v[i], b = v[(i + 1) % n];
        if (onSeg(a, b, p)) return 1;
        if ((a.y > p.y) != (b.y > p.y) && (cross(a, b, p) > 0) == (b.y > a.y)) in ^= 1; // ray to +x crosses edge
    }
    return in ? 2 : 0;
}

// ---- polygon is simple ----
// n>=3 vertices, no repeated/crossing/touching edges (180-degree vertices are OK). O(n^2)
bool isSimple(const vector<P>& v) {
    int n = v.size();
    for (int i = 0; i < n; i++) { // neighbours: must not fold back onto each other
        P a = v[(i + n - 1) % n], b = v[i], c = v[(i + 1) % n];
        if (cross(b, a, c) == 0 && dot(b, a, c) >= 0) return false;
    }
    for (int i = 0; i < n; i++)
        for (int j = i + 2; j < n; j++) {
            if (i == 0 && j == n - 1) continue;
            if (segInter(v[i], v[i + 1], v[j], v[(j + 1) % n])) return false;
        }
    return true;
}

// ---- convex hull ----
// strict hull vertices (no collinear points), CCW, starting at the lexicographically smallest point; duplicates ignored. O(n^3), n <= 100
// idea: a,b is a hull edge iff every point is left of ab, or on the segment ab
vector<P> hullBrute(vector<P> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n <= 2) return p;
    vi nxt(n, -1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            bool ok = true;
            for (int k = 0; k < n; k++)
                if (cross(p[i], p[j], p[k]) < 0 || (cross(p[i], p[j], p[k]) == 0 && !onSeg(p[i], p[j], p[k]))) ok = false;
            if (ok) nxt[i] = j;
        }
    vector<P> h;
    for (int i = 0; ; i = nxt[i]) { // p[0] is always a hull vertex
        h.push_back(p[i]);
        if (nxt[i] == 0) break;
    }
    return h;
}

// ---- closest pair ----
// min squared distance between two different points (equal points allowed, distance 0). O(n^2), n >= 2   (KACTL stress-tests/geometry/ClosestPair.cpp)
ll closest2(const vector<P>& v) {
    ll best = LLONG_MAX;
    for (int i = 0; i < (int)v.size(); i++)
        for (int j = i + 1; j < (int)v.size(); j++) best = min(best, dist2(v[i], v[j]));
    return best;
}

// ---- farthest pair ----
// max squared distance between two points. O(n^2)
ll farthest2(const vector<P>& v) {
    ll best = 0;
    for (int i = 0; i < (int)v.size(); i++)
        for (int j = i + 1; j < (int)v.size(); j++) best = max(best, dist2(v[i], v[j]));
    return best;
}

// ---- minimum enclosing circle ----
// {x, y, r} of the smallest circle containing all points: try every pair (as diameter) and triple (circumcircle). O(n^4), n <= 40
array<double, 3> mecBrute(const vector<P>& v) {
    int n = v.size();
    array<double, 3> best = {0, 0, 1e18};
    auto tryC = [&](double x, double y, double r) {
        if (r >= best[2]) return;
        for (P p : v) if (hypot(p.x - x, p.y - y) > r + 1e-9) return;
        best = {x, y, r};
    };
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++) {
            double x = (v[i].x + v[j].x) / 2.0, y = (v[i].y + v[j].y) / 2.0;
            tryC(x, y, hypot(v[i].x - x, v[i].y - y));
            for (int k = j + 1; k < n; k++) {
                ll d = 2 * cross(v[i], v[j], v[k]);
                if (d == 0) continue;
                P b = {v[j].x - v[i].x, v[j].y - v[i].y}, c = {v[k].x - v[i].x, v[k].y - v[i].y};
                ll b2 = b.x * b.x + b.y * b.y, c2 = c.x * c.x + c.y * c.y;
                double ox = (double)(c.y * b2 - b.y * c2) / d, oy = (double)(b.x * c2 - c.x * b2) / d; // center rel. to v[i]
                tryC(v[i].x + ox, v[i].y + oy, hypot(ox, oy));
            }
        }
    return best;
}

// ---- lattice points of a polygon ----
// {strictly inside, on boundary} integer points of a simple polygon, scanning its bounding box. O(area * n); Pick: area2 = 2*in + bd - 2
pair<ll, ll> latticeCount(const vector<P>& v) {
    P lo = v[0], hi = v[0];
    for (P p : v) lo = {min(lo.x, p.x), min(lo.y, p.y)}, hi = {max(hi.x, p.x), max(hi.y, p.y)};
    pair<ll, ll> r = {0, 0};
    for (ll x = lo.x; x <= hi.x; x++)
        for (ll y = lo.y; y <= hi.y; y++) {
            int c = inPoly(v, {x, y});
            if (c == 2) r.first++;
            if (c == 1) r.second++;
        }
    return r;
}

// ---- points inside triangle ----
// how many of the points are inside or on triangle abc (any orientation, non-degenerate). O(n)
int countInTri(P a, P b, P c, const vector<P>& pts) {
    int cnt = 0;
    for (P p : pts) {
        ll x = cross(a, b, p), y = cross(b, c, p), z = cross(c, a, p);
        if ((x >= 0 && y >= 0 && z >= 0) || (x <= 0 && y <= 0 && z <= 0)) cnt++;
    }
    return cnt;
}

int main() { // reads what gen.cpp's default main prints (polygon + query point); other formats: see gen.cpp
    int n;
    scanf("%d", &n);
    vector<P> v(n);
    for (P& p : v) scanf("%lld %lld", &p.x, &p.y);
    P q;
    scanf("%lld %lld", &q.x, &q.y);
    printf("%d\n", inPoly(v, q));
    // other formats from gen.cpp:
    // point set (n, points):  printf("%lld\n", closest2(v));  farthest2(v);  hullBrute(v);  mecBrute(v)
    // two segments:           read a b c d, printf("%d\n", segInter(a, b, c, d));
    // triangle:               latticeCount({a, b, c}), area2({a, b, c})
}

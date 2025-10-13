#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

struct P
{
    double x, y;

    P(double x = 0.0,double y = 0.0):x(x),y(y){};

    void input() {
        cin >> x >> y;
    }
    void output() {
        cout<<x<<" "<<y;
    }
    // Vector subtraction: this - b
    P operator-(const P &b) const {
        return {x - b.x, y - b.y};
    }

    // Subtract and assign: this -= b
    void operator-=(const P &b) {
        x -= b.x;
        y -= b.y;
    }

    // Vector addition: this + b
    P operator+(const P &b) const {
        return {x + b.x, y + b.y};
    }

    // Add and assign: this += b
    void operator+=(const P &b) {
        x += b.x;
        y += b.y;
    }

    // Scalar multiplication: this * k
    P operator*(double k) const {
        return {x * k, y * k};
    }

    // Scalar division: this / k (⚠️ Integer division)
    P operator/(double k) const {
        return {x / k, y / k};
    }

    // 2D Cross product: this × b = x*b.y - y*b.x
    // Geometric meaning: area of parallelogram formed by this and b (signed)
    double operator*(const P &b) const {
        return x * b.y - y * b.x;
    }

    // Dot product: this • b = x*b.x + y*b.y
    // Geometric meaning: projection component, used for angle and length
    double operator&(const P &b) const {
        return x * b.x + y * b.y;
    }

    // Signed double area of triangle (this, b, c)
    // Formula: (b - this) × (c - this)
    double triangle(const P &b, const P &c) const {
        return (b - *this) * (c - *this);
    }

    // Euclidean distance between two points: √[(x1 - x2)² + (y1 - y2)²]
    double dist(const P &b) const {
        return sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y));
    }

    // Squared length (norm²) of vector: x² + y²
    double length2() const {
        return x * x + y * y;
    }

    // Length (magnitude) of vector: √(x² + y²)
    double length() const {
        return sqrt(length2());
    }

    // Unit vector: (x / |v|, y / |v|), direction with length = 1
    P unit() const {
        double len = length();
        return {x / len, y / len};
    }

    // Projection of this onto vector b
    // Formula: proj_b(this) = b * [(this • b) / |b|²]
    P project_onto(const P &b) const {
        double dot = (*this & b);
        double len2 = b.length2();
        return b * (dot / (double)len2);
    }
    P reflect(const P &b) const {
        double dot = (*this & b);
        double len2 = b.length2();
        P proj = b * (dot / len2);  // projection of *this onto b
        return proj * 2 - *this;    // reflect: 2·proj - original
    }
    // Distance from point to line through points a and b
    // Formula: |(b - a) × (this - a)| / |b - a|
    // Geometric meaning: height from point to line
    //1. Distance from *this to infinite line AB
    double dist_to_line(const P &a, const P &b) const {
        P ab = b - a;
        P ap = *this - a;
        return abs((ab * ap)) / ab.length();
    }
    // 2) Distance to ray AB (starts at A, goes through B):
    double dist_to_ray(const P &a, const P &b) const {
        P ab = b - a, ap = *this - a;
        double ab2 = ab.length2();
        double u   = (ap & ab) / ab2;
        if (u < 0.0) {
            // if projection falls "behind" A, closest point is A
            return ap.length();
        }
        // else drop perpendicular
        return fabs(ab * ap) / ab.length();
    }
    // 3) Distance to segment AB (finite [A,B]):
    double dist_to_segment(const P &a, const P &b) const {
        P ab = b - a, ap = *this - a;
        double ab2 = ab.length2();
        double u   = (ap & ab) / ab2;
        if (u < 0.0) {
            // before A
            return ap.length();
        }
        else if (u > 1.0) {
            // beyond B
            return (*this - b).length();
        }
        // between A and B
        return fabs(ab * ap) / ab.length();
    }
    // Distance between two segments AB and CD
    // to use instead of std::
    // P::dist_to_segment(P a, P b, P c, P d);
    static double dist_segments(const P &a, const P &b, const P &c, const P &d) {
        // Check if segments intersect (cross product test)
        auto ccw = [](const P &a, const P &b, const P &c) {
            return (b - a) * (c - a) > 0;
        };
        bool intersect = (ccw(a, b, c) != ccw(a, b, d)) && (ccw(c, d, a) != ccw(c, d, b));
        if (intersect) return 0.0;

        // Else, return min of 4 point-to-segment distances
        return min({
            c.dist_to_segment(a, b),
            d.dist_to_segment(a, b),
            a.dist_to_segment(c, d),
            b.dist_to_segment(c, d)
        });
    }
    // Distance between two rays AB and CD
    static double dist_rays(const P &A, const P &B, const P &C, const P &D) {
        const double EPS = 1e-9;
        P AB = B - A;
        P CD = D - C;

        if (AB.length2() < EPS && CD.length2() < EPS)
            return A.dist(C);
        if (AB.length2() < EPS)
            return A.dist_to_ray(C, D);
        if (CD.length2() < EPS)
            return C.dist_to_ray(A, B);

        double cross = AB * CD;
        P AC = C - A;

        if (fabs(cross) > EPS) {
            double t = (AC * CD) / cross;
            double s = (AC * AB) / cross;
            if (t >= -EPS && s >= -EPS) return 0.0;
        } else {
            // Parallel or collinear
            if (fabs((C - A) * CD) < EPS) {
                // Collinear
                double proj1 = ((C - A) & AB) / AB.length2();
                double proj2 = ((A - C) & CD) / CD.length2();
                if (proj1 >= -EPS || proj2 >= -EPS) return 0.0;
            }
        }

        // No valid intersection; get min point-to-ray distance
        return min({
            A.dist_to_ray(C, D),
            C.dist_to_ray(A, B)
        });
    }
    double angle_with(const P &b) const 
    {
        return acos((*this & b) / (length() * b.length()));
    }
    // Static function: returns unit vector in direction of angle bisector between a and b
    static P bisector(const P &a, const P &b) {
        P ua = a.unit();
        P ub = b.unit();
        P sum = ua + ub;

        if (sum.length2() < 1e-9) {
            // a and b are in opposite directions, bisector undefined
            return {0, 0}; // or handle separately
        }
        return sum.unit(); // normalize the sum to get unit bisector
        // P p1,p2,p3;
        // p1.input();
        // p2.input();
        // p3.input();
        // P x=p2-p1,y=p3-p1;
        // x=x.unit();
        // y=y.unit();
        // P z=x+y;
        // double a=z.y;
        // double b=-z.x;
        // double c=-(a*p1.x+b*p1.y);
        // if(abs(c)<=eps) c=0;
        // cout<<fx(7)<<a<<" "<<b<<" "<<c;
    }

    // Point equality: returns true if (x, y) == (b.x, b.y)
    bool operator==(const P &b) const {
        return x == b.x && y == b.y;
    }

    // Lexicographical comparison for sorting (by x, then y)
    bool operator<(const P &b) const {
        return tie(x, y) < tie(b.x, b.y);
    }
};
P translate(P a, P v){
    return a+v;
}
P scale(P a, P ref, double factor){
    return ref+(a-ref)*factor;
}
P rotate(P a, P ref, double angle){
    //for cw negate the angle
    P v=a-ref;
    P c={cos(angle),sin(angle)};
    P res={v.x * c.x - v.y * c.y, v.x * c.y + v.y * c.x};
    return (ref+res);
}
P general(P a, P acpy, P b, P bcpy, P r) {
    if (a == b) return acpy;
    P ab = b - a;
    P ar = r - a;
    double t = (ar & ab) / ab.length2(); // projection factor along ab
    return acpy + (bcpy - acpy) * t;
}
// Sorts points by polar angle with respect to reference point O
P O; // Global reference point for sorting

bool polar_cmp(const P &a, const P &b) {
    P va = a - O;
    P vb = b - O;

    int half_a = (va.y > 0 || (va.y == 0 && va.x >= 0));
    int half_b = (vb.y > 0 || (vb.y == 0 && vb.x >= 0));

    if (half_a != half_b)
        return half_a > half_b;

    return (va * vb) > 0; // Cross product to compare angles
};


const long double INF = 1e18;
struct edge {
    int to;
    long double w;
    bool operator<(const edge &e) const { return w > e.w; }
};

vector<long double> Dijkstra(const vector<vector<edge>> &adjList, int n, int src) {
    vector<long double> dist(n, INF);
    priority_queue<edge> q;
    q.push({src, 0.0L});
    while (!q.empty()) {
        auto mn = q.top(); q.pop();
        int idx = mn.to;
        if (dist[idx] < INF) continue;
        dist[idx] = mn.w;
        for (auto &ed : adjList[idx]) {
            if (dist[ed.to] == INF) {
                q.push({ed.to, dist[idx] + ed.w});
            }
        }
    }
    return dist;
}



void solve(int test_case) {
    ld x,y; cin>>x>>y;
    P st(x,y);
    int n; cin>>n;
    vector<pair<P,P>>v(n);
    for(int i = 0 ; i < n ; i++){
        ld a,b,c,d; cin>>a>>b>>c>>d;
        v[i].first = P(a,b); v[i].second = P(c,d);
    }
    vector<vector<edge>>g(n+1);
    for(int i = 0 ; i < n ; i++){
        ld d = st.dist_to_segment(v[i].first,v[i].second);
        g[0].push_back({i+1,d});
        g[i+1].push_back({0,d});
    }
    for(int i = 0 ; i < n ; i++){
        for(int j = 0; j < n ; j++){
            ld d = P::dist_segments(v[i].first,v[i].second,v[j].first,v[j].second);
            g[i+1].push_back({j+1,d});
        }
    }
    auto dis = Dijkstra(g,n+1,0);
   // for(int i = 0 ; i <= n ;i++) cout<<fixed<<setprecision(6)<<dis[i]<<ln;
    int q; cin>>q;
    while(q--){
        ld a,b; cin>>a>>b;
        P p(a,b);
        ld mn = p.dist(st);
    //    cout<<fixed<<setprecision(8)<<p.dist_to_segment(v[0].first,v[0].second)<<ln;
        for(int i = 1 ; i <= n ; i++) mn = min(mn , dis[i] + p.dist_to_segment(v[i-1].first,v[i-1].second));
        cout<<fixed<<setprecision(8)<<mn<<ln;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
  
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}
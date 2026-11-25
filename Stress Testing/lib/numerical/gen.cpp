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
// ===== NUMERICAL =====
typedef vector<ll> vl;
typedef vector<vl> vvl;

vl randVL(int n, ll lo, ll hi) { // n values in [lo,hi]
    vl v(n);
    for (ll& x : v) x = rnd(lo, hi);
    return v;
}

vl randPoly(int d, ll lo, ll hi) { // coefficients a[0..d] (a[i] = coef of x^i), leading coef != 0 (needs [lo,hi] != {0})
    vl a = randVL(d + 1, lo, hi);
    while (d > 0 && a[d] == 0) a[d] = rnd(lo, hi);
    return a;
}

vvl randMat(int n, int m, ll lo, ll hi) { // n x m matrix, entries in [lo,hi]
    vvl A(n);
    for (vl& r : A) r = randVL(m, lo, hi);
    return A;
}

vvl randSingular(int n, ll lo, ll hi) { // n x n (n >= 2) matrix with two equal rows, so det = 0
    vvl A = randMat(n, n, lo, hi);
    int i = rnd(0, n - 1), j = (i + rnd(1, n - 1)) % n;
    A[i] = A[j];
    return A;
}

void randSystem(int n, int m, ll lo, ll hi, vvl& A, vl& b, vl& x) { // A (n x m), x (m) in [lo,hi], b = A*x (so >= 1 solution exists)
    A = randMat(n, m, lo, hi);
    x = randVL(m, lo, hi);
    b.assign(n, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) b[i] += A[i][j] * x[j];
}

void randRec(int k, ll p, vl& c, vl& init) { // order-k recurrence S[i] = sum_j c[j]*S[i-1-j] (mod p); c[k], init[k] in [0,p)
    c = randVL(k, 0, p - 1);
    init = randVL(k, 0, p - 1);
}

vl randSubset(int k, ll lo, ll hi) { // sequence of size 2^k for subset (AND/OR/XOR) transforms
    return randVL(1 << k, lo, hi);
}

ll randMod() { // a small / famous prime modulus
    ll P[] = {2, 3, 5, 7, 13, 101, 998244353, 1000000007};
    return P[rnd(0, 7)];
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    int n = rnd(1, 8), m = rnd(1, 8); // polynomials of length n and m
    vl a = randPoly(n - 1, -5, 5), b = randPoly(m - 1, -5, 5);
    cout << n << " " << m << "\n";
    for (ll x : a) cout << x << " ";
    cout << "\n";
    for (ll x : b) cout << x << " ";
    cout << "\n";
}

/* Other main bodies (paste in place of the one above):

// square matrix + power: n e, then matrix (exact if entries stay small)
int n = rnd(1, 5);
cout << n << " " << rnd(0, 6) << "\n";
for (vl& r : randMat(n, n, -3, 3)) { for (ll x : r) cout << x << " "; cout << "\n"; }

// linear system with a known solution: n m, A rows, then b
int n = rnd(1, 5), m = rnd(1, 5);
vvl A; vl b, x;
randSystem(n, m, -5, 5, A, b, x);
cout << n << " " << m << "\n";
for (vl& r : A) { for (ll v : r) cout << v << " "; cout << "\n"; }
for (ll v : b) cout << v << " ";
cout << "\n";

// linear recurrence mod p: k p idx, c, init
ll p = randMod();
int k = rnd(1, 5);
vl c, init;
randRec(k, p, c, init);
cout << k << " " << p << " " << rnd(0, 50) << "\n";
for (ll v : c) cout << v << " ";
cout << "\n";
for (ll v : init) cout << v << " ";
cout << "\n";

// subset convolution: k, a, b (size 2^k)
int k = rnd(0, 4);
cout << k << "\n";
for (ll v : randSubset(k, -3, 3)) cout << v << " ";
cout << "\n";
for (ll v : randSubset(k, -3, 3)) cout << v << " ";
cout << "\n";
*/

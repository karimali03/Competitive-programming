#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<double> vd;

// Brute-force numerical routines. Functions end in B so they never clash with your own names.
// Modulus p: p = 0 means "exact, no modulus"; otherwise inputs must be in [0,p) with p <= 3e9, output is in [0,p).

// ---- polynomials (a[i] = coefficient of x^i) ----
vl polyMulB(const vl& a, const vl& b, ll p = 0) { // O(|a||b|); naive FFT/NTT check, size |a|+|b|-1
    if (a.empty() || b.empty()) return {};
    vl c(a.size() + b.size() - 1, 0);
    for (int i = 0; i < (int)a.size(); i++) for (int j = 0; j < (int)b.size(); j++) {
        c[i + j] += a[i] * b[j];
        if (p) c[i + j] %= p;
    }
    return c;
}

ll polyEvalB(const vl& a, ll x, ll p = 0) { // sum a[i]*x^i, powers built one by one, O(n)
    ll s = 0, pw = 1;
    if (p) x %= p, pw %= p;
    for (ll c : a) {
        s += c * pw, pw *= x;
        if (p) s %= p, pw %= p;
    }
    return s;
}

double polyEvalD(const vd& a, double x) { // Horner with doubles, O(n)
    double s = 0;
    for (int i = (int)a.size() - 1; i >= 0; i--) s = s * x + a[i];
    return s;
}

bool checkInterpB(const vd& a, const vd& xs, const vd& ys, double eps = 1e-6) { // does polynomial a pass through all (xs[i], ys[i])? O(n^2)
    for (int i = 0; i < (int)xs.size(); i++)
        if (fabs(polyEvalD(a, xs[i]) - ys[i]) > eps * max(1.0, fabs(ys[i]))) return 0;
    return 1;
}

vector<complex<double>> dftB(const vector<complex<double>>& a) { // out[k] = sum_x a[x]*exp(2 pi i k x / n), O(n^2) (from KACTL stress-tests/numerical/FastFourierTransform.cpp)
    int n = a.size();
    vector<complex<double>> r(n);
    for (int k = 0; k < n; k++) for (int x = 0; x < n; x++) r[k] += a[x] * polar(1.0, 2 * M_PI * k * x / n);
    return r;
}

// ---- matrices ----
vvl matMulB(const vvl& A, const vvl& B, ll p = 0) { // (n x k)*(k x m), O(nkm)
    int n = A.size(), k = B.size(), m = B[0].size();
    vvl C(n, vl(m, 0));
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) for (int t = 0; t < k; t++) {
        C[i][j] += A[i][t] * B[t][j];
        if (p) C[i][j] %= p;
    }
    return C;
}

vvl matPowB(const vvl& A, ll e, ll p = 0) { // A^e (square) by e multiplications, O(e n^3), e <= 1e5
    int n = A.size();
    vvl R(n, vl(n, 0));
    for (int i = 0; i < n; i++) R[i][i] = p == 1 ? 0 : 1;
    while (e--) R = matMulB(R, A, p);
    return R;
}

ll detPermB(const vvl& A, ll p = 0) { // determinant = sum over permutations of sign*product, O(n!*n), n <= 8
    int n = A.size();
    vi perm(n);
    iota(perm.begin(), perm.end(), 0);
    ll d = 0;
    do {
        ll t = 1;
        for (int i = 0; i < n; i++) {
            t *= A[i][perm[i]];
            if (p) t %= p;
        }
        int inv = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) inv += perm[i] > perm[j];
        d += inv % 2 ? -t : t;
        if (p) d = (d % p + p) % p;
    } while (next_permutation(perm.begin(), perm.end()));
    return d;
}

int rankModB(vvl A, ll p) { // rank of matrix over GF(p), p prime; Gaussian elimination, inverse by Fermat, O(n^3 log p)
    int n = A.size(), m = A[0].size(), r = 0;
    auto pw = [&](ll b, ll e) { ll s = 1; for (; e; e >>= 1, b = b * b % p) if (e & 1) s = s * b % p; return s; };
    for (int c = 0; c < m && r < n; c++) {
        int s = r;
        while (s < n && A[s][c] == 0) s++;
        if (s == n) continue;
        swap(A[s], A[r]);
        ll inv = pw(A[r][c], p - 2);
        for (int i = r + 1; i < n; i++) {
            ll f = A[i][c] * inv % p;
            for (int j = c; j < m; j++) A[i][j] = ((A[i][j] - f * A[r][j]) % p + p) % p;
        }
        r++;
    }
    return r;
}

bool checkSolveB(const vvl& A, const vl& x, const vl& b) { // exact: A*x == b ? O(nm)
    for (int i = 0; i < (int)A.size(); i++) {
        ll s = 0;
        for (int j = 0; j < (int)x.size(); j++) s += A[i][j] * x[j];
        if (s != b[i]) return 0;
    }
    return 1;
}

bool checkSolveD(const vector<vd>& A, const vd& x, const vd& b, double eps = 1e-6) { // doubles: |A*x - b| <= eps (relative) ? O(nm)
    for (int i = 0; i < (int)A.size(); i++) {
        double s = 0;
        for (int j = 0; j < (int)x.size(); j++) s += A[i][j] * x[j];
        if (fabs(s - b[i]) > eps * max(1.0, fabs(b[i]))) return 0;
    }
    return 1;
}

// ---- recurrences ----
ll linRecB(const vl& init, const vl& c, ll k, ll p) { // S[k] for S[i] = sum_j c[j]*S[i-1-j] (mod p), S[0..n-1] = init; direct iteration, O(k n), k <= 1e7
    int n = c.size();
    vl S(init);
    for (ll i = n; i <= k; i++) {
        ll s = 0;
        for (int j = 0; j < n; j++) s = (s + c[j] * S[i - 1 - j]) % p;
        S.push_back(s);
    }
    return S[k] % p;
}

bool checkRecB(const vl& s, const vl& c, ll p) { // does recurrence c reproduce the whole sequence s (mod p)? use to check Berlekamp-Massey, O(|s||c|)
    for (int i = c.size(); i < (int)s.size(); i++) {
        ll t = 0;
        for (int j = 0; j < (int)c.size(); j++) t = (t + c[j] * s[i - 1 - j]) % p;
        if (t != s[i] % p) return 0;
    }
    return 1;
}

// ---- subset convolution ----
vl subsetConvB(const vl& a, const vl& b, char t) { // c[i op j] += a[i]*b[j], t in {'&','|','^'}, O(4^k), k <= 10 (from KACTL stress-tests/numerical/FastSubsetTransform.cpp)
    int n = a.size();
    vl c(n, 0);
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
        c[t == '&' ? i & j : t == '|' ? i | j : i ^ j] += a[i] * b[j];
    return c;
}

// ---- integration ----
double integralB(function<double(double)> f, double a, double b, int n = 1000000) { // midpoint Riemann sum with n slices, O(n)
    double h = (b - a) / n, s = 0;
    for (int i = 0; i < n; i++) s += f(a + (i + 0.5) * h);
    return s * h;
}

int main() { // reads "n m", poly A (n coeffs), poly B (m coeffs); prints A*B
    int n, m;
    cin >> n >> m;
    vl a(n), b(m);
    for (ll& x : a) cin >> x;
    for (ll& x : b) cin >> x;
    for (ll x : polyMulB(a, b)) cout << x << " ";
    cout << "\n";
}

/* Other main bodies (match the ones in gen.cpp):

// n e, matrix -> A^e, and det of A (n <= 8)
int n; ll e; cin >> n >> e;
vvl A(n, vl(n));
for (vl& r : A) for (ll& x : r) cin >> x;
for (vl& r : matPowB(A, e)) { for (ll x : r) cout << x << " "; cout << "\n"; }
cout << detPermB(A) << "\n";

// n m, A, b -> rank mod 101 and whether the matrix has full row rank (solution checking: checkSolveB(A, x, b))
int n, m; cin >> n >> m;
vvl A(n, vl(m)); vl b(n);
for (vl& r : A) for (ll& x : r) cin >> x;
for (ll& x : b) cin >> x;
for (vl& r : A) for (ll& x : r) x = (x % 101 + 101) % 101;
cout << rankModB(A, 101) << "\n";

// k p idx, c, init -> S[idx]
int k; ll p, idx; cin >> k >> p >> idx;
vl c(k), init(k);
for (ll& x : c) cin >> x;
for (ll& x : init) cin >> x;
cout << linRecB(init, c, idx, p) << "\n";

// k, a, b -> AND, OR, XOR convolutions
int k; cin >> k;
vl a(1 << k), b(1 << k);
for (ll& x : a) cin >> x;
for (ll& x : b) cin >> x;
for (char t : {'&', '|', '^'}) {
    for (ll x : subsetConvB(a, b, t)) cout << x << " ";
    cout << "\n";
}
*/

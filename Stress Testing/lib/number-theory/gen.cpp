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
// ===== NUMBER THEORY =====
bool isP(ll n) { // trial division, n <= ~1e12
    if (n < 2) return 0;
    for (ll i = 2; i * i <= n; i++) if (n % i == 0) return 0;
    return 1;
}

ll randPrime(ll lo, ll hi) { // prime in [lo,hi], hi <= ~1e12; loops forever if there is none
    ll x = rnd(lo, hi);
    while (!isP(x)) x = x < hi ? x + 1 : lo;
    return x;
}

ll randComposite(ll lo, ll hi) { // composite in [lo,hi], lo >= 4, hi <= ~1e12
    ll x;
    do x = rnd(lo, hi); while (isP(x));
    return x;
}

ll randSmooth(ll hi) { // product of random primes <= 47, <= hi (many divisors / small factors)
    int P[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
    ll x = 1, p;
    while (x <= hi / (p = P[rnd(0, 14)])) x *= p;
    return x;
}

ll randPower(ll hi) { // b^e with b >= 2, e >= 2, <= hi (hi >= 4, hi <= ~9e18)
    ll b = rnd(2, min<ll>(1000, sqrtl(hi))), r = b * b;
    for (int e = rnd(0, 5); e-- && r <= hi / b;) r *= b;
    return r;
}

ll randSquare(ll hi) { // perfect square in [0,hi], hi <= 1e18
    ll s = rnd(0, sqrtl(hi));
    return s * s;
}

ll edgeVal(ll hi) { // a classic edge value <= hi (0,1,2,primes near limits, 2^k, 1e18...)
    ll E[] = {0, 1, 2, 3, 4, 6, 998244353, 1000000007, 1000000000, 2147483647, 2147483648LL, 4294967291LL,
              1000000000000000000LL, 1000000000000000003LL, 1LL << 62, LLONG_MAX};
    ll x;
    do x = E[rnd(0, 15)]; while (x > hi);
    return x;
}

ll randPrimeMod(ll hi) { // prime modulus <= hi (hi >= 2): a famous one when it fits, else a random prime
    ll K[] = {2, 3, 5, 7, 998244353, 1000000007, 2147483647};
    ll x = K[rnd(0, 6)];
    return x <= hi && randBool() ? x : randPrime(2, hi);
}

pair<ll, ll> coprimePair(ll hi) { // (a, m): m in [2,hi], a in [1,m-1], gcd(a,m) = 1
    ll m = rnd(2, hi), a;
    do a = rnd(1, m - 1); while (__gcd(a, m) != 1);
    return {a, m};
}

vector<ll> randCRT(ll hi) { // {a, m, b, n}, m,n in [1,hi], hi <= 3e9; x = a (mod m), x = b (mod n) always solvable
    ll m = rnd(1, hi), n = rnd(1, hi), l = m / __gcd(m, n) * n, x = rnd(0, l - 1);
    return {x % m, m, x % n, n};
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    pair<ll, ll> p = coprimePair(1000);
    cout << p.first << " " << p.second << "\n";
}

/* Other main bodies (paste in place of the one above):

// one integer n, prime or composite
cout << (randBool() ? randPrime(2, 1000000) : randComposite(4, 1000000)) << "\n";

// one integer n, special shape (smooth / perfect power / square / edge value)
int t = rnd(0, 3);
cout << (t == 0 ? randSmooth(1000000) : t == 1 ? randPower(1000000) : t == 2 ? randSquare(1000000) : edgeVal(1000000)) << "\n";

// CRT: a m b n
vector<ll> c = randCRT(1000);
cout << c[0] << " " << c[1] << " " << c[2] << " " << c[3] << "\n";

// discrete log / mod sqrt: a b p (p prime)
ll p = randPrimeMod(1000);
cout << rnd(0, p - 1) << " " << rnd(0, p - 1) << " " << p << "\n";
*/

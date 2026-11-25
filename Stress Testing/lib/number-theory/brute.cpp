#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// Brute-force number theory. Functions end in B so they never clash with your own names.
// Args are positive unless said otherwise. "-1" means no answer.

// ---- gcd / lcm ----
ll gcdB(ll a, ll b) { // gcd by trying every d, O(min(a,b)), <= 1e7; gcdB(0,b) = b
    if (!a || !b) return a + b;
    ll g = 1;
    for (ll d = 1; d <= min(a, b); d++) if (a % d == 0 && b % d == 0) g = d;
    return g;
}

ll lcmB(ll a, ll b) { // smallest positive multiple of a divisible by b, O(b), b <= 1e7
    ll m = a;
    while (m % b) m += a;
    return m;
}

bool checkEuclid(ll a, ll b, ll g, ll x, ll y) { // does (g,x,y) from your extgcd satisfy g=gcd(a,b), ax+by=g ? O(min(a,b))
    return g == gcdB(a, b) && a * x + b * y == g;
}

// ---- primes / factors ----
bool isPrimeB(ll n) { // trial division, O(sqrt n), n <= 1e13
    if (n < 2) return 0;
    for (ll i = 2; i * i <= n; i++) if (n % i == 0) return 0;
    return 1;
}

vector<ll> factorB(ll n) { // prime factors with multiplicity, ascending (n=1 -> {}), O(sqrt n), n <= 1e13
    vector<ll> f;
    for (ll p = 2; p * p <= n; p++) while (n % p == 0) f.push_back(p), n /= p;
    if (n > 1) f.push_back(n);
    return f;
}

vector<ll> primesUpToB(int n) { // all primes <= n, each by trial division, O(n sqrt n), n <= 1e5
    vector<ll> p;
    for (int i = 2; i <= n; i++) if (isPrimeB(i)) p.push_back(i);
    return p;
}

ll isqrtB(ll n) { // floor(sqrt(n)), O(sqrt n), n <= 1e14
    ll x = 0;
    while ((x + 1) * (x + 1) <= n) x++;
    return x;
}

// ---- divisors / arithmetic functions ----
vector<ll> divisorsB(ll n) { // all divisors of n, ascending, O(n), n <= 1e7 (count = sz, sum = accumulate)
    vector<ll> d;
    for (ll i = 1; i <= n; i++) if (n % i == 0) d.push_back(i);
    return d;
}

ll phiB(ll n) { // Euler phi: count of k in [1,n] with gcd(k,n)=1, O(n log n), n <= 1e7
    ll c = 0;
    for (ll k = 1; k <= n; k++) c += __gcd(k, n) == 1;
    return c;
}

int mobiusB(ll n) { // Moebius mu(n): 0 if some p^2 | n, else (-1)^(#primes), O(sqrt n), n <= 1e13
    int r = 1;
    for (ll p = 2; p * p <= n; p++) if (n % p == 0) {
        n /= p, r = -r;
        if (n % p == 0) return 0;
    }
    return n > 1 ? -r : r;
}

// ---- modular arithmetic ----
ll modpowB(ll b, ll e, ll m) { // b^e mod m by e multiplications, O(e), e <= 1e7, m <= 3e9 (e=0 -> 1 % m)
    ll r = 1 % m;
    b %= m;
    while (e--) r = r * b % m;
    return r;
}

ll modInvB(ll a, ll m) { // x in [0,m) with a*x = 1 (mod m), else -1; O(m), m <= 1e7
    a %= m;
    for (ll x = 0; x < m; x++) if (a * x % m == 1 % m) return x;
    return -1;
}

ll orderB(ll a, ll m) { // smallest k >= 1 with a^k = 1 (mod m), -1 if gcd(a,m) != 1; O(m), m <= 1e7
    ll cur = a % m;
    for (ll k = 1; k <= m; k++) {
        if (cur == 1 % m) return k;
        cur = cur * a % m;
    }
    return -1;
}

ll primRootB(ll p) { // smallest primitive root of prime p, O(p^2), p <= 3000
    for (ll g = 1; g < p; g++) if (orderB(g, p) == p - 1) return g;
    return -1;
}

ll dlogB(ll a, ll b, ll m) { // smallest x >= 1 with a^x = b (mod m), else -1, O(m), m <= 1e7
    ll cur = a % m;           // x = 0 is NOT allowed (matches KACTL modLog; from KACTL stress-tests/number-theory/ModLog.cpp)
    for (ll x = 1; x <= m; x++) {
        if (cur == b % m) return x;
        cur = cur * a % m;
    }
    return -1;
}

vector<ll> sqrtModB(ll a, ll p) { // all x in [0,p) with x^2 = a (mod p), ascending, O(p), p <= 1e7
    vector<ll> r;
    for (ll x = 0; x < p; x++) if (x * x % p == a % p) r.push_back(x);
    return r;
}

ll crtB(ll a, ll m, ll b, ll n) { // smallest x >= 0 with x = a (mod m), x = b (mod n), else -1; O(n), m*n <= 4e18
    a = (a % m + m) % m, b = (b % n + n) % n;
    for (ll k = 0; k < n; k++) if ((a + k * m) % n == b) return a + k * m;
    return -1;
}

ll binomB(int n, int k, ll p) { // C(n,k) mod p from Pascal's triangle, O(n^2), n <= 5000, p <= 3e9
    vector<ll> row(n + 2, 0);
    row[0] = 1 % p;
    for (int i = 1; i <= n; i++) for (int j = i; j >= 1; j--) row[j] = (row[j] + row[j - 1]) % p;
    return k < 0 || k > n ? 0 : row[k];
}

// ---- sums over arithmetic progressions ----
ll rmod(ll x, ll m) { return (x % m + m) % m; } // always in [0,m)
ll rdiv(ll x, ll m) { return (x - rmod(x, m)) / m; } // floor division, m > 0

ll modsumB(ll to, ll c, ll k, ll m) { // sum_{i<to} (c+k*i) mod m (in [0,m)), O(to), to <= 1e7 (from KACTL stress-tests/number-theory/ModSum.cpp)
    ll res = 0;
    for (ll i = 0; i < to; i++) res += rmod(c + k * i, m);
    return res;
}

ll divsumB(ll to, ll c, ll k, ll m) { // sum_{i<to} floor((c+k*i)/m), O(to), to <= 1e7 (from KACTL stress-tests/number-theory/ModSum.cpp)
    ll res = 0;
    for (ll i = 0; i < to; i++) res += rdiv(c + k * i, m);
    return res;
}

int main() { // reads "a m", prints the inverse of a mod m (-1 if none)
    ll a, m;
    cin >> a >> m;
    cout << modInvB(a, m) << "\n";
}

/* Other main bodies (match the ones in gen.cpp):

// n -> is it prime, its factorization, phi, mu, divisors
ll n; cin >> n;
cout << isPrimeB(n) << " " << phiB(n) << " " << mobiusB(n) << " " << divisorsB(n).size() << "\n";
for (ll p : factorB(n)) cout << p << " ";
cout << "\n";

// a m b n -> crt
ll a, m, b, n; cin >> a >> m >> b >> n;
cout << crtB(a, m, b, n) << "\n";

// a b p -> discrete log, all square roots of a, primitive root
ll a, b, p; cin >> a >> b >> p;
cout << dlogB(a, b, p) << " " << sqrtModB(a, p).size() << " " << primRootB(p) << "\n";
*/

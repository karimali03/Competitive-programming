#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


// Brute-force bit tricks. Functions end in B so they never clash with your own names.
// op is one of '^' '&' '|'. Arrays are 0-indexed, values >= 0. "-1" means no answer.

int ap(int x, int y, char op) { return op == '^' ? x ^ y : op == '&' ? x & y : x | y; } // x op y

// ---- pairs ----
ll sumPairB(const vi& a, char op) { // sum of a[i] op a[j] over all pairs i<j, O(n^2)
    ll s = 0;
    for (size_t i = 0; i < a.size(); i++) for (size_t j = i + 1; j < a.size(); j++) s += ap(a[i], a[j], op);
    return s;
}
int maxXorPairB(const vi& a) { // max a[i]^a[j] over i<j, -1 if n < 2, O(n^2)
    int r = -1;
    for (size_t i = 0; i < a.size(); i++) for (size_t j = i + 1; j < a.size(); j++) r = max(r, a[i] ^ a[j]);
    return r;
}
int maxAndPairB(const vi& a) { // max a[i]&a[j] over i<j, -1 if n < 2, O(n^2)
    int r = -1;
    for (size_t i = 0; i < a.size(); i++) for (size_t j = i + 1; j < a.size(); j++) r = max(r, a[i] & a[j]);
    return r;
}
ll zeroPairsB(const vi& a) { // number of pairs i<j with a[i] & a[j] == 0, O(n^2)
    ll c = 0;
    for (size_t i = 0; i < a.size(); i++) for (size_t j = i + 1; j < a.size(); j++) c += (a[i] & a[j]) == 0;
    return c;
}

// ---- subarrays ----
ll sumSubB(const vi& a, char op) { // sum over all subarrays [l,r] of (a[l] op ... op a[r]), O(n^3)
    ll s = 0;
    for (size_t l = 0; l < a.size(); l++) for (size_t r = l; r < a.size(); r++) {
        int v = a[l];
        for (size_t i = l + 1; i <= r; i++) v = ap(v, a[i], op);
        s += v;
    }
    return s;
}
ll countXorB(const vi& a, int k) { // number of subarrays with XOR == k, O(n^3)
    ll c = 0;
    for (size_t l = 0; l < a.size(); l++) for (size_t r = l; r < a.size(); r++) {
        int v = 0;
        for (size_t i = l; i <= r; i++) v ^= a[i];
        c += v == k;
    }
    return c;
}

// ---- subsets ----
vi subsetXorsB(const vi& a) { // sorted distinct XORs of all 2^n subsets (empty subset gives 0), O(2^n * n), n <= 20
    set<int> s;
    int n = a.size();
    for (int m = 0; m < (1 << n); m++) {
        int v = 0;
        for (int i = 0; i < n; i++) if (m >> i & 1) v ^= a[i];
        s.insert(v);
    }
    return vi(s.begin(), s.end()); // size = 2^rank, back() = max subset XOR
}
vector<ll> sosB(const vector<ll>& f, int n) { // g[mask] = sum of f[sub] over all submasks sub of mask, O(3^n), n <= 12
    vector<ll> g(1 << n, 0);
    for (int mask = 0; mask < (1 << n); mask++)
        for (int sub = mask;; sub = (sub - 1) & mask) {
            g[mask] += f[sub];
            if (sub == 0) break;
        }
    return g;
}

// ---- ranges of integers ----
ll popRangeB(ll l, ll r, int k) { // number of x in [l,r] with popcount(x) == k, O(r - l), r <= 1e7
    ll c = 0;
    for (ll x = l; x <= r; x++) c += __builtin_popcountll(x) == k;
    return c;
}
ll countBitsB(ll n, ll mask, ll val) { // number of x in [0,n] with (x & mask) == val, O(n), n <= 1e7
    ll c = 0;
    for (ll x = 0; x <= n; x++) c += (x & mask) == val;
    return c;
}
ll xorToB(ll n) { // 1 ^ 2 ^ ... ^ n, O(n), n <= 1e8
    ll r = 0;
    for (ll i = 1; i <= n; i++) r ^= i;
    return r;
}
ll popSumB(ll n) { // popcount(1) + ... + popcount(n), O(n), n <= 1e7
    ll s = 0;
    for (ll i = 1; i <= n; i++) s += __builtin_popcountll(i);
    return s;
}

// ---- Gray code / popcount ----
bool isGrayB(const vi& g, int n) { // is g a cyclic n-bit Gray code: all 2^n values distinct, neighbours (and last/first) differ in 1 bit, O(2^n)
    int m = 1 << n;
    if ((int)g.size() != m) return 0;
    set<int> s(g.begin(), g.end());
    if ((int)s.size() != m || *s.begin() < 0 || *s.rbegin() >= m) return 0;
    for (int i = 0; i < m && m > 1; i++) if (__builtin_popcount(g[i] ^ g[(i + 1) % m]) != 1) return 0;
    return 1;
}
ll nextSamePopB(ll x) { // smallest y > x with the same popcount, -1 if x == 0, O(y - x)
    if (x == 0) return -1;
    ll y = x + 1;
    while (__builtin_popcountll(y) != __builtin_popcountll(x)) y++;
    return y;
}

// ---- known formulas (stress these against the brutes) ----
ll xorToF(ll n) { // 1^2^...^n by n % 4: n, 1, n+1, 0
    ll t[4] = {n, 1, n + 1, 0};
    return t[n % 4];
}

ll sumPairF(const vi& a, char op) { // per-bit contribution, O(31 n): c1 ones, c0 zeros -> XOR c1*c0, AND C(c1,2), OR C(n,2)-C(c0,2)
    ll n = a.size(), s = 0;
    for (int b = 0; b < 31; b++) {
        ll c1 = 0, c0;
        for (int x : a) c1 += x >> b & 1;
        c0 = n - c1;
        ll pairs = op == '^' ? c1 * c0 : op == '&' ? c1 * (c1 - 1) / 2 : n * (n - 1) / 2 - c0 * (c0 - 1) / 2;
        s += pairs << b;
    }
    return s;
}

ll sumSubF(const vi& a, char op) { // sum over subarrays: XOR = pair sum of prefix XORs; AND/OR = per bit count runs of all-1 / all-0
    int n = a.size();
    if (op == '^') {
        vi p(n + 1, 0);
        for (int i = 0; i < n; i++) p[i + 1] = p[i] ^ a[i];
        return sumPairF(p, '^');
    }
    ll s = 0, total = (ll)n * (n + 1) / 2;
    for (int b = 0; b < 31; b++) {
        ll run = 0, good = 0; // good = subarrays where every element has bit == (op == '&')
        for (int x : a) {
            run = (x >> b & 1) == (op == '&') ? run + 1 : 0;
            good += run;
        }
        s += (op == '&' ? good : total - good) << b;
    }
    return s;
}

ll countXorF(const vi& a, int k) { // subarrays with XOR == k: prefix XOR + map (pairs of prefixes p[j]^p[i] == k), O(n log n)
    map<int, ll> cnt;
    cnt[0] = 1;
    ll c = 0;
    int p = 0;
    for (int x : a) {
        p ^= x;
        c += cnt[p ^ k];
        cnt[p]++;
    }
    return c;
}

int bs[31]; // linear basis (xor basis): bs[i] has top bit i or is 0
void basisInsert(int x) { // O(31)
    for (int i = 30; i >= 0; i--) if (x >> i & 1) {
        if (!bs[i]) { bs[i] = x; return; }
        x ^= bs[i];
    }
}
int basisMax() { // max XOR of any subset of inserted numbers
    int r = 0;
    for (int i = 30; i >= 0; i--) r = max(r, r ^ bs[i]);
    return r;
}
int basisRank() { int r = 0; for (int i = 0; i < 31; i++) r += bs[i] != 0; return r; } // reachable XORs = 2^rank

int maxXorPairF(const vi& a) { // max XOR of two elements, greedy bit by bit with prefix set, O(31 n), n >= 2
    int res = 0;
    for (int b = 30; b >= 0; b--) {
        set<int> pre;
        for (int x : a) pre.insert(x >> b);
        int t = (res >> b) | 1; // try to set bit b: need prefixes u, v with u ^ v == t
        for (int u : pre) if (pre.count(u ^ t)) { res |= 1 << b; break; }
    }
    return res;
}
int maxAndPairF(const vi& a) { // max AND of two elements, greedy: keep bit if >= 2 elements contain the candidate, O(31 n), n >= 2
    int res = 0;
    for (int b = 30; b >= 0; b--) {
        int c = 0;
        for (int x : a) c += (x & (res | 1 << b)) == (res | 1 << b);
        if (c >= 2) res |= 1 << b;
    }
    return res;
}

vector<ll> sosF(vector<ll> f, int n) { // submask sums, O(n 2^n): for each bit, add f[mask without bit] into f[mask]
    for (int i = 0; i < n; i++) for (int m = 0; m < (1 << n); m++) if (m >> i & 1) f[m] += f[m ^ (1 << i)];
    return f;
}
ll zeroPairsF(const vi& a, int bits) { // pairs i<j with a[i]&a[j]==0 via SOS over counts, values < 2^bits
    int full = (1 << bits) - 1;
    vector<ll> cnt(1 << bits, 0);
    for (int x : a) cnt[x]++;
    cnt = sosF(cnt, bits); // cnt[m] = number of elements that are submasks of m
    ll s = 0;
    for (int x : a) s += cnt[full ^ x] - (x == 0); // ordered pairs; x & x == 0 only for x == 0 (remove self pair)
    return s / 2;
}

ll onesAtBitF(ll n, int b) { // how many x in [0,n] have bit b set: full blocks of 2^(b+1) give 2^b each, plus the partial block
    ll blk = 1LL << (b + 1), tail = (n + 1) % blk;
    return (n + 1) / blk * (blk / 2) + max(0LL, tail - blk / 2);
}
ll popSumF(ll n) { // popcount(0) + ... + popcount(n), sum over bits of onesAtBitF
    ll s = 0;
    for (int b = 0; b < 40; b++) s += onesAtBitF(n, b);
    return s;
}
ll popRangeF(ll n, int k) { // x in [0,n] with popcount k: for each set bit i of n+1 (top down) add C(i, k - ones so far), O(60^2)
    ll C[64][64] = {};
    for (int i = 0; i < 64; i++) for (int j = 0; j <= i; j++) C[i][j] = j == 0 ? 1 : C[i - 1][j - 1] + (j < i ? C[i - 1][j] : 0);
    ll N = n + 1, r = 0;
    int ones = 0;
    for (int i = 62; i >= 0; i--) if (N >> i & 1) {
        if (k - ones >= 0 && k - ones <= i) r += C[i][k - ones];
        ones++;
    }
    return r;
}

ll grayF(ll i) { return i ^ (i >> 1); } // i-th Gray code
ll nextSamePopF(ll x) { // Gosper's hack, x > 0
    ll c = x & -x, r = x + c;
    return (((r ^ x) >> 2) / c) | r;
}

int main() { // reads "n k" then n values, prints sum of pair XOR / AND / OR, sum of subarray XOR / AND / OR, #subarrays with XOR k
    int n, k;
    cin >> n >> k;
    vi a(n);
    for (int& x : a) cin >> x;
    cout << sumPairB(a, '^') << " " << sumPairB(a, '&') << " " << sumPairB(a, '|') << "\n";
    cout << sumSubB(a, '^') << " " << sumSubB(a, '&') << " " << sumSubB(a, '|') << "\n";
    cout << countXorB(a, k) << "\n";
}

/* Other main bodies (replace the body above; pair each with the matching gen main):

// "n k" + array: max pairs, zero-AND pairs, subset XORs
int n, k; cin >> n >> k;
vi a(n);
for (int& x : a) cin >> x;
vi s = subsetXorsB(a);
cout << maxXorPairB(a) << " " << maxAndPairB(a) << " " << zeroPairsB(a) << " " << s.size() << " " << s.back() << "\n";

// "l r k"
ll l, r; int k; cin >> l >> r >> k;
cout << popRangeB(l, r, k) << "\n";

// "n": XOR 1..n, sum of popcounts 1..n, next same popcount, count with low 2 bits == 1, Gray code check
int n; cin >> n;
vi g(1 << (n % 6));
for (int i = 0; i < (int)g.size(); i++) g[i] = i ^ (i >> 1);
cout << xorToB(n) << " " << popSumB(n) << " " << nextSamePopB(n) << " " << countBitsB(n, 3, 1) << " " << isGrayB(g, n % 6) << "\n";

// "n" then 2^n values: SOS
int n; cin >> n;
vector<ll> f(1 << n);
for (ll& x : f) cin >> x;
for (ll x : sosB(f, n)) cout << x << " ";
cout << "\n";
*/

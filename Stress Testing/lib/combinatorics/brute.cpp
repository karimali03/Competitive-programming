#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


// Brute-force combinatorics: literally enumerate and count. Functions end in B so they never clash with your own names.
// Counts are exact (ll); pass p only where noted (p = 0 -> exact). Reduce with % p yourself when comparing to a mod-p formula.

// ---- subsets / binomials ----
ll binomB(int n, int k, ll p) { // C(n,k): count k-element subsets among all 2^n masks, O(2^n), n <= 20 (p = 0 -> exact)
    ll c = 0;
    for (int m = 0; m < (1 << n); m++) c += __builtin_popcount(m) == k;
    return p ? c % p : c;
}

// ---- permutations ----
ll multisetPermB(string s) { // number of distinct rearrangements of s (next_permutation on sorted), O(n! * n), n <= 9
    sort(s.begin(), s.end());
    ll c = 0;
    do c++; while (next_permutation(s.begin(), s.end()));
    return c;
}

ll permFixedB(int n, int k) { // permutations of n elements with exactly k fixed points, O(n! * n), n <= 9
    vi p(n);
    iota(p.begin(), p.end(), 0);
    ll c = 0;
    do {
        int f = 0;
        for (int i = 0; i < n; i++) f += p[i] == i;
        c += f == k;
    } while (next_permutation(p.begin(), p.end()));
    return c;
}
ll derangeB(int n) { return permFixedB(n, 0); } // derangements (no fixed point), n <= 9

ll stirling1B(int n, int k) { // unsigned Stirling 1st kind: permutations of n with exactly k cycles, O(n! * n), n <= 9
    vi p(n);
    iota(p.begin(), p.end(), 0);
    ll c = 0;
    do {
        vi seen(n, 0);
        int cyc = 0;
        for (int i = 0; i < n; i++) if (!seen[i]) {
            cyc++;
            for (int j = i; !seen[j]; j = p[j]) seen[j] = 1;
        }
        c += cyc == k;
    } while (next_permutation(p.begin(), p.end()));
    return c;
}

ll inversionsB(int n, int k) { // permutations of n with exactly k inversions (pairs i<j, p[i]>p[j]), O(n! * n^2), n <= 9
    vi p(n);
    iota(p.begin(), p.end(), 0);
    ll c = 0;
    do {
        int inv = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) inv += p[i] > p[j];
        c += inv == k;
    } while (next_permutation(p.begin(), p.end()));
    return c;
}

// ---- bracket sequences ----
ll catalanB(int n) { // balanced bracket sequences of length 2n: test all 2^(2n) bit strings, O(4^n * n), n <= 10
    ll c = 0;
    for (int m = 0; m < (1 << (2 * n)); m++) {
        int d = 0;
        bool ok = true;
        for (int i = 0; i < 2 * n; i++) {
            d += ((m >> i) & 1) ? 1 : -1;
            if (d < 0) ok = false;
        }
        c += ok && d == 0;
    }
    return c;
}

// ---- set partitions ----
void rgs(int i, int n, int used, vector<ll>& cnt) { // restricted growth strings: element i joins block 0..used (used = new block)
    if (i == n) { cnt[used]++; return; }
    for (int b = 0; b <= used; b++) rgs(i + 1, n, max(used, b + 1), cnt);
}
vector<ll> setPartB(int n) { // cnt[k] = number of set partitions of n elements into exactly k non-empty blocks, O(Bell(n) * n), n <= 11
    vector<ll> cnt(n + 1, 0);
    rgs(0, n, 0, cnt);
    return cnt;
}
ll stirling2B(int n, int k) { return k < 0 || k > n ? 0 : setPartB(n)[k]; } // Stirling 2nd kind S(n,k), n <= 11
ll bellB(int n) { vector<ll> c = setPartB(n); return accumulate(c.begin(), c.end(), 0LL); } // Bell number, n <= 11

// ---- integer partitions / compositions ----
ll partRec(int rem, int mx, int left, bool distinct) { // parts in non-increasing order, each <= mx, at most `left` parts
    if (rem == 0) return 1;
    if (left == 0) return 0;
    ll c = 0;
    for (int v = 1; v <= min(rem, mx); v++) c += partRec(rem - v, distinct ? v - 1 : v, left - 1, distinct);
    return c;
}
ll partitionsB(int n, int k, bool distinct) { // partitions of n into at most k parts (k = n: all); distinct = parts all different, n <= 50
    return partRec(n, n, k, distinct);
}

ll compRec(int rem, int k, int lo) { // sequences of k ints, each >= lo, summing to rem
    if (k == 0) return rem == 0;
    ll c = 0;
    for (int v = lo; v <= rem; v++) c += compRec(rem - v, k - 1, lo);
    return c;
}
ll compositionsB(int n, int k, int lo) { // sequences of k ints >= lo (lo=1 compositions, lo=0 stars and bars) summing to n, n <= 15
    return compRec(n, k, lo);
}

// ---- lattice paths ----
ll latticeB(const vector<string>& g, int r = 0, int c = 0) { // right/down paths top-left -> bottom-right avoiding '#', R+C <= 24
    int R = g.size(), C = g[0].size();
    if (g[r][c] == '#') return 0;
    if (r == R - 1 && c == C - 1) return 1;
    ll s = 0;
    if (r + 1 < R) s += latticeB(g, r + 1, c);
    if (c + 1 < C) s += latticeB(g, r, c + 1);
    return s;
}

// ---- inclusion-exclusion / Burnside checks ----
ll surjB(int n, int k) { // functions {1..n} -> {1..k} hitting every value (= k! S(n,k)), O(k^n * n), k^n <= 1e7
    ll tot = 1;
    for (int i = 0; i < n; i++) tot *= k;
    ll c = 0;
    for (ll m = 0, x; m < tot; m++) {
        int seen = 0;
        x = m;
        for (int i = 0; i < n; i++) seen |= 1 << (x % k), x /= k;
        c += seen == (1 << k) - 1;
    }
    return c;
}

ll necklaceB(int n, int k) { // strings of length n over k letters counted up to rotation (set of minimal rotations), k^n <= 1e6
    ll tot = 1;
    for (int i = 0; i < n; i++) tot *= k;
    set<string> seen;
    for (ll m = 0, x; m < tot; m++) {
        string s(n, 'a');
        x = m;
        for (int i = 0; i < n; i++) s[i] = 'a' + x % k, x /= k;
        string best = s;
        for (int r = 0; r < n; r++) rotate(s.begin(), s.begin() + 1, s.end()), best = min(best, s);
        seen.insert(best);
    }
    return seen.size();
}

// ---- known formulas (stress these against the brutes) ----
// What you would actually submit. Mod-p versions need p prime and p > n (use p = 1e9+7); compare with brute % p.
ll pw(ll b, ll e, ll p) { // b^e mod p
    ll r = 1 % p;
    for (b %= p; e; e >>= 1, b = b * b % p) if (e & 1) r = r * b % p;
    return r;
}

ll P; vector<ll> fact, ifact;
void initFact(int N, ll p) { // factorials and inverse factorials up to N, p prime > N
    P = p, fact.assign(N + 1, 1), ifact.assign(N + 1, 1);
    for (int i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % p;
    ifact[N] = pw(fact[N], p - 2, p);
    for (int i = N; i > 0; i--) ifact[i - 1] = ifact[i] * i % p;
}
ll binomF(int n, int k) { return k < 0 || k > n ? 0 : fact[n] * ifact[k] % P * ifact[n - k] % P; } // C(n,k) mod P
ll catalanF(int n) { return (binomF(2 * n, n) - binomF(2 * n, n + 1) + P) % P; } // C(2n,n) - C(2n,n+1), needs initFact(>= 2n+1)

ll derangeF(int n, ll p) { // D(n) = (n-1)(D(n-1) + D(n-2)), D(0)=1, D(1)=0
    vector<ll> d(max(n + 1, 2), 0);
    d[0] = 1 % p;
    for (int i = 2; i <= n; i++) d[i] = (i - 1) * (d[i - 1] + d[i - 2]) % p;
    return d[n];
}
ll permFixedF(int n, int k) { return binomF(n, k) * derangeF(n - k, P) % P; } // permutations with exactly k fixed points

vector<vector<ll>> stirling2F(int n, ll p) { // S[i][j] = S[i-1][j-1] + j*S[i-1][j]
    vector<vector<ll>> S(n + 1, vector<ll>(n + 1, 0));
    S[0][0] = 1 % p;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++) S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % p;
    return S;
}
vector<vector<ll>> stirling1F(int n, ll p) { // c[i][j] = c[i-1][j-1] + (i-1)*c[i-1][j]  (unsigned)
    vector<vector<ll>> c(n + 1, vector<ll>(n + 1, 0));
    c[0][0] = 1 % p;
    for (int i = 1; i <= n; i++) for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j - 1] + (i - 1) * c[i - 1][j]) % p;
    return c;
}
ll bellF(int n, ll p) { // Bell(n) = sum_k S(n,k)
    vector<vector<ll>> S = stirling2F(n, p);
    ll s = 0;
    for (ll x : S[n]) s = (s + x) % p;
    return s;
}

ll partitionsF(int n, int k, ll p) { // partitions of n into parts <= k (= at most k parts), coin-change DP over part sizes
    vector<ll> d(n + 1, 0);
    d[0] = 1 % p;
    for (int v = 1; v <= min(n, k); v++) for (int i = v; i <= n; i++) d[i] = (d[i] + d[i - v]) % p;
    return d[n];
}
ll distinctPartF(int n, ll p) { // partitions of n into distinct parts, 0/1 knapsack over part sizes
    vector<ll> d(n + 1, 0);
    d[0] = 1 % p;
    for (int v = 1; v <= n; v++) for (int i = n; i >= v; i--) d[i] = (d[i] + d[i - v]) % p;
    return d[n];
}

ll starsBarsF(int n, int k, int lo) { // sequences of k ints >= lo summing to n: C(n - k*lo + k - 1, k - 1), needs initFact(>= n+k)
    if (k == 0) return n == 0;
    int m = n - k * lo;
    return m < 0 ? 0 : binomF(m + k - 1, k - 1);
}

ll surjF(int n, int k) { // inclusion-exclusion: onto functions = sum_i (-1)^i C(k,i) (k-i)^n, needs initFact(>= k)
    ll s = 0;
    for (int i = 0; i <= k; i++) s = (s + (i % 2 ? -1 : 1) * binomF(k, i) * pw(k - i, n, P) % P + P) % P;
    return s;
}

ll inversionsF(int n, int k, ll p) { // d[i][j] = sum_{t=0}^{min(j,i-1)} d[i-1][j-t]  (new last element has t bigger elements before it)
    vector<vector<ll>> d(n + 1, vector<ll>(k + 1, 0));
    d[0][0] = 1 % p;
    for (int i = 1; i <= n; i++) for (int j = 0; j <= k; j++) for (int t = 0; t <= min(j, i - 1); t++)
        d[i][j] = (d[i][j] + d[i - 1][j - t]) % p;
    return d[n][k];
}

ll multisetPermF(const string& s) { // n! / prod(cnt!) mod P, needs initFact(>= |s|)
    int cnt[256] = {};
    for (unsigned char c : s) cnt[c]++;
    ll r = fact[s.size()];
    for (int c = 0; c < 256; c++) r = r * ifact[cnt[c]] % P;
    return r;
}

ll necklaceF(int n, int k) { // Burnside: (1/n) * sum_{i<n} k^gcd(i,n), exact (n=0 -> 1)
    if (n == 0) return 1;
    ll s = 0;
    for (int i = 0; i < n; i++) {
        ll t = 1;
        for (int j = 0; j < __gcd(i, n); j++) t *= k;
        s += t;
    }
    return s / n;
}

ll latticeF(const vector<string>& g, ll p) { // dp[r][c] = dp[r-1][c] + dp[r][c-1] on free cells
    int R = g.size(), C = g[0].size();
    vector<vector<ll>> d(R, vector<ll>(C, 0));
    for (int r = 0; r < R; r++) for (int c = 0; c < C; c++) {
        if (g[r][c] == '#') continue;
        if (r == 0 && c == 0) d[r][c] = 1 % p;
        else d[r][c] = ((r ? d[r - 1][c] : 0) + (c ? d[r][c - 1] : 0)) % p;
    }
    return d[R - 1][C - 1];
}

int main() { // reads "n k p", prints C(n,k) mod p (p = 0 -> exact)
    int n, k;
    ll p;
    cin >> n >> k >> p;
    cout << binomB(n, k, p) << "\n";
}

/* Other main bodies (replace the body above; pair each with the matching gen main):

// "n k": every count that takes (n, k)
int n, k; cin >> n >> k;
cout << catalanB(n) << " " << derangeB(n) << " " << bellB(n) << " " << stirling2B(n, k) << " " << stirling1B(n, k) << "\n";
cout << permFixedB(n, k) << " " << partitionsB(n, k, 0) << " " << partitionsB(n, n, 1) << " " << inversionsB(n, k) << "\n";
cout << compositionsB(n, k, 1) << " " << compositionsB(n, k, 0) << " " << surjB(n, k) << " " << necklaceB(n, k) << "\n";

// multiset string
string s; cin >> s;
cout << multisetPermB(s) << "\n";

// grid: "r c" then r rows
int r, c; cin >> r >> c;
vector<string> g(r);
for (auto& row : g) cin >> row;
cout << latticeB(g) << "\n";
*/

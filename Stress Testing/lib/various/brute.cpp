#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define all(x) x.begin(), x.end()

// Patterns to copy into your own brute force:
//   all subsets:      for (int mask = 0; mask < (1 << n); mask++) for (int i = 0; i < n; i++) if (mask >> i & 1) { /* i is in the subset */ }
//   all permutations: vi p(n); iota(all(p), 0); do { /* use p */ } while (next_permutation(all(p)));  // p must start sorted

// ---- LIS by trying all subsets ---- O(2^n * n), n <= 20. Length of longest strictly increasing (weak = false) or non-decreasing (weak = true) subsequence
// from KACTL stress-tests/various/LIS.cpp
int lisBrute(const vi& a, bool weak) {
    int n = a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int prev = INT_MIN, cnt = 0;
        bool ok = true;
        for (int i = 0; i < n && ok; i++) if (mask >> i & 1) {
            if (cnt && (weak ? a[i] < prev : a[i] <= prev)) ok = false;
            prev = a[i], cnt++;
        }
        if (ok) best = max(best, cnt);
    }
    return best;
}

// ---- 0/1 knapsack by all subsets ---- O(2^n * n), n <= 20. items (weight, value); max total value with total weight <= W
ll knapsack01(const vector<pii>& it, int W) {
    int n = it.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll w = 0, v = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) w += it[i].first, v += it[i].second;
        if (w <= W) best = max(best, v);
    }
    return best;
}

// ---- subset sum by all subsets ---- O(2^n * n), n <= 20. Is there a subset (possibly empty) summing exactly to T?
bool subsetSum(const vi& a, ll T) {
    int n = a.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        ll s = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) s += a[i];
        if (s == T) return true;
    }
    return false;
}

// ---- max XOR of a subset by all subsets ---- O(2^n * n), n <= 20 (empty subset gives 0)
int maxSubsetXor(const vi& a) {
    int n = a.size(), best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        int x = 0;
        for (int i = 0; i < n; i++) if (mask >> i & 1) x ^= a[i];
        best = max(best, x);
    }
    return best;
}

// ---- coin change, min number of coins ---- plain recursion, exponential: coins positive, T <= ~15. Unlimited coins, -1 if impossible
int coinMin(const vi& c, int T) {
    if (T == 0) return 0;
    int best = -1;
    for (int x : c) if (x <= T) {
        int r = coinMin(c, T - x);
        if (r >= 0 && (best < 0 || r + 1 < best)) best = r + 1;
    }
    return best;
}

// ---- coin change, number of ways (order does not matter) ---- plain recursion, exponential: T <= ~20, coins positive (duplicates count as different coins)
// at coin i: either use it once more (stay on i) or move to coin i+1
ll coinWays(const vi& c, int T, int i = 0) {
    if (T == 0) return 1;
    if (T < 0 || i == (int)c.size()) return 0;
    return coinWays(c, T - c[i], i) + coinWays(c, T, i + 1);
}

// ---- LCS length ---- plain recursion, exponential: |s| + |t| <= ~20
int lcsRec(const string& s, const string& t, int i = 0, int j = 0) {
    if (i == (int)s.size() || j == (int)t.size()) return 0;
    if (s[i] == t[j]) return 1 + lcsRec(s, t, i + 1, j + 1);
    return max(lcsRec(s, t, i + 1, j), lcsRec(s, t, i, j + 1));
}

// ---- edit distance (insert / delete / replace, cost 1 each) ---- plain recursion, exponential: |s|, |t| <= ~7
int editRec(const string& s, const string& t, int i = 0, int j = 0) {
    if (i == (int)s.size()) return t.size() - j;
    if (j == (int)t.size()) return s.size() - i;
    return min({editRec(s, t, i + 1, j + 1) + (s[i] != t[j]), editRec(s, t, i + 1, j) + 1, editRec(s, t, i, j + 1) + 1});
}

// ---- TSP by all permutations ---- O(n! * n), n <= 9. d = n x n distance matrix (0-indexed), shortest cycle through all cities (returns 0 for n = 1)
ll tspBrute(const vector<vi>& d) {
    int n = d.size();
    vi p(n);
    iota(all(p), 0);
    ll best = LLONG_MAX;
    do {
        ll c = d[p[n - 1]][p[0]];
        for (int i = 0; i + 1 < n; i++) c += d[p[i]][p[i + 1]];
        best = min(best, c);
    } while (next_permutation(p.begin() + 1, p.end())); // city 0 fixed first
    return best;
}

// ---- max weight set of non-overlapping intervals by all subsets ---- O(2^n * n^2), n <= 15. jobs (l, r, w) half-open [l, r): touching ends (r == next l) are allowed
ll maxWeightIntervals(const vector<array<int, 3>>& j) {
    int n = j.size();
    ll best = 0;
    for (int mask = 0; mask < (1 << n); mask++) {
        ll w = 0;
        bool ok = true;
        for (int a = 0; a < n && ok; a++) if (mask >> a & 1) {
            w += j[a][2];
            for (int b = a + 1; b < n; b++)
                if ((mask >> b & 1) && j[a][0] < j[b][1] && j[b][0] < j[a][1]) ok = false;
        }
        if (ok) best = max(best, w);
    }
    return best;
}

// ---- count grid paths ---- plain DFS, exponential: R, C <= ~10. g = R strings of '.' / '#', moves right/down from (0,0) to (R-1,C-1), 0 if start/end blocked
ll gridPaths(const vector<string>& g, int i = 0, int j = 0) {
    if (i >= (int)g.size() || j >= (int)g[0].size() || g[i][j] == '#') return 0;
    if (i == (int)g.size() - 1 && j == (int)g[0].size() - 1) return 1;
    return gridPaths(g, i + 1, j) + gridPaths(g, i, j + 1);
}

// ---- max subarray sum ---- O(n^2). Nonempty subarray, 0-indexed vector
ll maxSubarray(const vi& a) {
    ll best = LLONG_MIN;
    for (int l = 0; l < (int)a.size(); l++) {
        ll s = 0;
        for (int r = l; r < (int)a.size(); r++) s += a[r], best = max(best, s);
    }
    return best;
}

// ---- count inversions ---- O(n^2). Pairs i < j with a[i] > a[j]
ll inversions(const vi& a) {
    ll c = 0;
    for (int i = 0; i < (int)a.size(); i++) for (int j = i + 1; j < (int)a.size(); j++) c += a[i] > a[j];
    return c;
}

// Reads what gen.cpp prints (n W / n lines "weight value").
// Prints: knapsack(value, cap W), subsetSum(weights, W), coinMin(weights, W), coinWays(weights, W), LIS(values), LIS non-decreasing(values)
int main() {
    int n, W;
    scanf("%d %d", &n, &W);
    vector<pii> it(n);
    vi w(n), v(n);
    for (int i = 0; i < n; i++) scanf("%d %d", &it[i].first, &it[i].second), w[i] = it[i].first, v[i] = it[i].second;
    printf("%lld %d %d %lld %d %d\n", knapsack01(it, W), subsetSum(w, W), coinMin(w, W), coinWays(w, W),
           lisBrute(v, false), lisBrute(v, true));
}

/* Matching main bodies for the other gen.cpp tests (replace main with one of these):

// two strings
int main() {
    char a[99], b[99];
    scanf("%s %s", a, b);
    printf("%d %d\n", lcsRec(a, b), editRec(a, b));
}

// TSP
int main() {
    int n;
    scanf("%d", &n);
    vector<vi> d(n, vi(n));
    for (auto& r : d) for (int& x : r) scanf("%d", &x);
    printf("%lld\n", tspBrute(d));
}

// weighted interval scheduling
int main() {
    int n;
    scanf("%d", &n);
    vector<array<int, 3>> j(n);
    for (auto& x : j) scanf("%d %d %d", &x[0], &x[1], &x[2]);
    printf("%lld\n", maxWeightIntervals(j));
}

// grid path counting
int main() {
    int R, C;
    scanf("%d %d", &R, &C);
    vector<string> g(R);
    for (auto& row : g) { char s[99]; scanf("%s", s); row = s; }
    printf("%lld\n", gridPaths(g));
}

// array: max subarray, inversions, max subset xor
int main() {
    int n;
    scanf("%d", &n);
    vi a(n);
    for (int& x : a) scanf("%d", &x);
    printf("%lld %lld %d\n", maxSubarray(a), inversions(a), maxSubsetXor(a));
}
*/

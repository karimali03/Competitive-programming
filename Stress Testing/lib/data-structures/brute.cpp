#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#define all(x) x.begin(), x.end()

// All functions take 1-indexed arrays a[1..n] (a[0] unused) and ranges 1 <= l <= r <= n unless noted.

// ---- updates ---- O(r-l+1) each
void pointSet(vi& a, int i, int x) { a[i] = x; }
void pointAdd(vi& a, int i, int x) { a[i] += x; }
void rangeAdd(vi& a, int l, int r, int x) { for (int i = l; i <= r; i++) a[i] += x; }
void rangeAssign(vi& a, int l, int r, int x) { for (int i = l; i <= r; i++) a[i] = x; }

// ---- range queries ---- O(r-l+1) each
ll rangeSum(const vi& a, int l, int r) { ll s = 0; for (int i = l; i <= r; i++) s += a[i]; return s; }
int rangeMin(const vi& a, int l, int r) { int m = a[l]; for (int i = l; i <= r; i++) m = min(m, a[i]); return m; }
int rangeMax(const vi& a, int l, int r) { int m = a[l]; for (int i = l; i <= r; i++) m = max(m, a[i]); return m; }
int rangeGcd(const vi& a, int l, int r) { int g = 0; for (int i = l; i <= r; i++) g = __gcd(g, abs(a[i])); return g; }
int rangeXor(const vi& a, int l, int r) { int x = 0; for (int i = l; i <= r; i++) x ^= a[i]; return x; }

// ---- count distinct in range ---- O(len log len) per query (Mo's brute)
int countDistinct(const vi& a, int l, int r) { set<int> s; for (int i = l; i <= r; i++) s.insert(a[i]); return s.size(); }

// ---- k-th smallest in range (k = 1 is the minimum) ---- O(len log len) per query
int kthInRange(const vi& a, int l, int r, int k) { vi b(a.begin() + l, a.begin() + r + 1); sort(all(b)); return b[k - 1]; }

// ---- count of elements < x in range ---- O(len) per query
int countLess(const vi& a, int l, int r, int x) { int c = 0; for (int i = l; i <= r; i++) c += a[i] < x; return c; }

// ---- 2D rectangle sum ---- O(R*C) per query. g[1..R][1..C], rectangle rows r1..r2, cols c1..c2
ll rectSum(const vector<vi>& g, int r1, int c1, int r2, int c2) {
    ll s = 0;
    for (int i = r1; i <= r2; i++) for (int j = c1; j <= c2; j++) s += g[i][j];
    return s;
}

// ---- max over lines at x ---- O(n) per query (LineContainer / CHT). lines (k, m): y = k*x + m, nonempty
// from KACTL stress-tests/data-structures/LineContainer.cpp (test2)
ll maxLineAt(const vector<pair<ll, ll>>& L, ll x) {
    ll best = LLONG_MIN;
    for (auto& p : L) best = max(best, p.first * x + p.second);
    return best;
}

// ---- Fenwick lower_bound ---- O(n). a[1..n] nonnegative. smallest p in [0, n] with a[1]+..+a[p] >= s, or n+1 if none
// from KACTL stress-tests/data-structures/FenwickTree.cpp (KACTL returns p-1)
int fenwickLowerBound(const vi& a, ll s) {
    int n = a.size() - 1;
    ll sum = 0;
    for (int p = 0; p <= n; p++) {
        if (p) sum += a[p];
        if (sum >= s) return p;
    }
    return n + 1;
}

// ---- multiset order statistics on a sorted vector ---- O(n log n) per op. s = sorted vector, 0-indexed
void msInsert(vi& s, int x) { s.push_back(x); sort(all(s)); }
void msErase(vi& s, int x) { auto it = find(all(s), x); if (it != s.end()) s.erase(it); } // erase one copy if present
int msKth(const vi& s, int k) { return s[k - 1]; } // k-th smallest, 1 <= k <= size
int msCountLess(const vi& s, int x) { int c = 0; for (int v : s) c += v < x; return c; }

// ---- union length of intervals ---- O(total length). intervals [l, r) half-open (l <= r)
int unionLength(const vector<pii>& iv) {
    set<int> cells;
    for (pii p : iv) for (int i = p.first; i < p.second; i++) cells.insert(i);
    return cells.size();
}

// ---- IntervalContainer brute ---- O(len). line[i] = 1 if cell i is covered. add = rangeAssign(line, l, r - 1, 1), remove = rangeAssign(..., 0)
// from KACTL stress-tests/various/IntervalContainer.cpp
vector<pii> segments(const vi& line) { // maximal runs of 1s as half-open [l, r) in increasing order (compare with set<pii> from KACTL addInterval)
    vector<pii> res;
    for (int i = 0; i < (int)line.size(); i++) {
        if (!line[i]) continue;
        if (!res.empty() && res.back().second == i) res.back().second++;
        else res.push_back({i, i + 1});
    }
    return res;
}

// ---- next greater element ---- O(n^2). res[i] = smallest j > i with a[j] > a[i], or n+1 if none
vi nextGreater(const vi& a) {
    int n = a.size() - 1;
    vi res(n + 1, n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) if (a[j] > a[i]) { res[i] = j; break; }
    return res;
}

// ---- sliding window min ---- O(n*k). res[i] = min of a[i..i+k-1] for i = 1..n-k+1
vi windowMin(const vi& a, int k) {
    int n = a.size() - 1;
    vi res(n + 1);
    for (int i = 1; i + k - 1 <= n; i++) res[i] = rangeMin(a, i, i + k - 1);
    return res;
}

// Reads what gen.cpp prints (n q / a[1..n] / q lines "t a b c").
// t=1: range add c to [a, b]. t=2: print sum min max gcd xor distinct median(k-th smallest) countLess(0) of [a, b].
int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    vi a(n + 1);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    while (q--) {
        int t, l, r, x;
        scanf("%d %d %d %d", &t, &l, &r, &x);
        if (t == 1) rangeAdd(a, l, r, x);
        else printf("%lld %d %d %d %d %d %d %d\n", rangeSum(a, l, r), rangeMin(a, l, r), rangeMax(a, l, r),
                    rangeGcd(a, l, r), rangeXor(a, l, r), countDistinct(a, l, r),
                    kthInRange(a, l, r, (r - l) / 2 + 1), countLess(a, l, r, 0));
    }
}

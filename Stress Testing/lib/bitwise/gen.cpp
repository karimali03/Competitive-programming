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

// ===== BITWISE =====
// Small values make equal elements, zero ANDs and repeated XOR prefixes likely.

// ---- randBitArr ----
// n values uniform in [0, 2^bits). bits = 3 gives 0..7.
vi randBitArr(int n, int bits) { return randVec(n, 0, (1 << bits) - 1); }

// ---- randRange ----
// Pair l <= r drawn from [lo, hi].
pii randRange(int lo, int hi) {
    int l = rnd(lo, hi), r = rnd(lo, hi);
    return {min(l, r), max(l, r)};
}

// ---- printArr ----
// Prints the array on one line.
void printArr(const vi& a) {
    for (size_t i = 0; i < a.size(); i++) cout << a[i] << " \n"[i + 1 == a.size()];
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());

    // "n k" then array with values 0..7 (pairs / subarrays / XOR == k / max pair / ...)
    int n = rnd(1, 8), k = rnd(0, 7);
    cout << n << ' ' << k << '\n';
    printArr(randBitArr(n, 3));

    /* Other ready-to-use main bodies (replace the body above; pair each with the matching brute main):

    // "n k" then array with wider values 0..2^b-1 (b random)
    int b = rnd(1, 10), n = rnd(1, 8), k = rnd(0, (1 << b) - 1);
    cout << n << ' ' << k << '\n';
    printArr(randBitArr(n, b));

    // "l r k": count x in [l, r] with popcount k
    auto [l, r] = randRange(0, 100);
    cout << l << ' ' << r << ' ' << rnd(0, 7) << '\n';

    // "n": XOR of 1..n, sum of popcounts 1..n, next number with same popcount, Gray code
    cout << rnd(0, 100) << '\n';

    // "n" then 2^n values: sum over submasks (SOS)
    int n = rnd(0, 6);
    cout << n << '\n';
    printArr(randBitArr(1 << n, 4));
    */
}

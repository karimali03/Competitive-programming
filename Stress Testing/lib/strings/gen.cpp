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

// ===== STRINGS =====
// Use a tiny alphabet ('a'..'b' or 'a'..'c') and short lengths (n <= 10): that is where bugs show up.

string periodicStr(int n, int p, int mut, char lo = 'a', char hi = 'b') { // length n = random block of length p repeated, then `mut` random positions changed
    string b = randStr(p, lo, hi), s;
    while ((int)s.size() < n) s += b;
    s.resize(n);
    while (mut-- > 0 && n > 0) s[rnd(0, n - 1)] = rnd(lo, hi);
    return s;
}

string fibStr(int n) { // prefix of length n of the Fibonacci word abaababa...
    string a = "a", b = "ab";
    while ((int)b.size() < n) { string c = b + a; a = b; b = c; }
    return b.substr(0, n);
}

string runsStr(int n, int maxRun, char lo = 'a', char hi = 'b') { // length n made of runs of one repeated char, each run length 1..maxRun
    string s;
    while ((int)s.size() < n) s += string(rnd(1, maxRun), (char)rnd(lo, hi));
    s.resize(n);
    return s;
}

string randPalindrome(int n, char lo = 'a', char hi = 'b') { // random palindrome of length n
    string s = randStr(n, lo, hi);
    for (int i = 0; i < n / 2; i++) s[n - 1 - i] = s[i];
    return s;
}

string randSubstr(const string& s, int len) { // random substring of s with exactly len chars (len <= |s|); use as a pattern that occurs
    int i = rnd(0, (int)s.size() - len);
    return s.substr(i, len);
}

string randRotation(const string& s) { // s rotated left by a random amount
    int k = rnd(0, (int)s.size() - 1);
    return s.substr(k) + s.substr(0, k);
}

vector<string> randPatterns(int k, int maxLen, char lo = 'a', char hi = 'b') { // k nonempty random patterns (duplicates possible), lengths 1..maxLen
    vector<string> v;
    while (k--) v.push_back(randStr(rnd(1, maxLen), lo, hi));
    return v;
}

vector<string> allStrings(int n, int k = 2) { // all k^n strings of length n over 'a'..'a'+k-1, in sorted order (exhaustive tests)
    vector<string> v = {""};
    while (n--) {
        vector<string> w;
        for (string& s : v) for (int c = 0; c < k; c++) w.push_back(s + char('a' + c));
        v = w;
    }
    return v;
}

// ---- extra: brackets ----
string randBrackets(int n) { // uniformly random BALANCED bracket sequence of length 2n (n >= 0): shuffle n '(' + (n+1) ')', rotate so all proper prefixes are >= 0 (cycle lemma), drop the last ')'
    string s = string(n, '(') + string(n + 1, ')');
    shuffle(s.begin(), s.end(), rng);
    int b = 0, mn = 0, at = 0;
    for (int i = 0; i <= 2 * n; i++) {
        b += s[i] == '(' ? 1 : -1;
        if (b < mn) mn = b, at = i + 1;
    }
    s = s.substr(at) + s.substr(0, at);
    s.pop_back();
    return s;
}

string randBracketsAny(int n) { // random '(' / ')' string of length n, usually NOT balanced (validity-check problems)
    return randStr(n, '(', ')');
}

// ---- extra: Thue-Morse / anti-hash ----
string thueMorse(int n) { // first n chars of the Thue-Morse word over {a,b}: abbabaab... (s[i] = parity of popcount(i)); the classic anti-hash test, breaks hashing mod 2^64 for n >= ~2^11, see antiHash64
    string s(n, 'a');
    for (int i = 0; i < n; i++) s[i] += __builtin_popcount(i) & 1;
    return s;
}

// Anti-hash test: polynomial hash mod 2^64 (unsigned long long overflow) is broken for EVERY odd base by Thue-Morse:
// S = thueMorse(2^k) and its complement T (swap a<->b) have the same hash once k >= 10 (length >= 1024; default k = 11 = 2048, safe margin). Returns {S, T}: different strings, equal hash.
pair<string, string> antiHash64(int k = 11) {
    string s = thueMorse(1 << k), t = s;
    for (char& c : t) c = 'a' + 'b' - c;
    return {s, t};
}

int main(int argc, char* argv[]) {
    rng.seed(argc > 1 ? atoll(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    // Example: text and pattern, one per line (pattern is a real substring half of the time).
    int n = rnd(1, 12);
    string s = periodicStr(n, rnd(1, 3), rnd(0, 1)), t;
    if (randBool()) t = randSubstr(s, rnd(1, n));
    else t = randStr(rnd(1, 4));
    printf("%s\n%s\n", s.c_str(), t.c_str());
}

/* Other main bodies (replace the one above; matching brute.cpp reading code is noted there):

// one string (prefix function, Z, suffix array, palindromes, distinct substrings, min rotation, period)
string s = rnd(0, 1) ? randStr(rnd(1, 12)) : fibStr(rnd(1, 12));
printf("%s\n", s.c_str());

// two strings (longest common substring, is rotation)
string s = randStr(rnd(1, 8)), t = randBool() ? randRotation(s) : randStr(rnd(1, 8));
printf("%s\n%s\n", s.c_str(), t.c_str());

// text + k patterns (Aho-Corasick style counting): text, k, then k patterns
string s = randStr(rnd(1, 12));
auto pats = randPatterns(rnd(1, 4), 3);
printf("%s\n%d\n", s.c_str(), (int)pats.size());
for (auto& p : pats) printf("%s\n", p.c_str());

// balanced brackets (isBalanced / countBalancedSubstrings): one string
string s = randBool() ? randBrackets(rnd(1, 6)) : randBracketsAny(rnd(1, 10));
printf("%s\n", s.c_str());

// exhaustive: put this in a loop instead of random tests, e.g. for (string& s : allStrings(6, 3)) { ... }
*/

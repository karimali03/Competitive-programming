#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

// 0-indexed everywhere. Strings are plain std::string.

// ---- all occurrences ----
// start indices where t occurs in s (overlapping ones included), increasing. O(n*m), n,m <= 1000
vi occurrences(const string& s, const string& t) {
    vi r;
    for (int i = 0; i + (int)t.size() <= (int)s.size(); i++)
        if (s.compare(i, t.size(), t) == 0) r.push_back(i);
    return r;
}

// ---- prefix function (KMP pi) ----
// p[i] = length of the longest proper prefix of s[0..i] that is also its suffix. O(n^3), n <= 300   (from KACTL stress-tests/strings/KMP.cpp)
vi prefixFunc(const string& s) {
    vi p(s.size());
    for (int i = 0; i < (int)s.size(); i++)
        for (int len = 0; len <= i; len++) // proper: len < i+1
            if (s.compare(0, len, s, i + 1 - len, len) == 0) p[i] = len;
    return p;
}

// ---- Z function ----
// z[i] = longest common prefix of s and s[i..]; z[0] = 0 like KACTL (use n if you need the usual convention). O(n^2), n <= 3000
vi zFunc(const string& s) {
    int n = s.size();
    vi z(n);
    for (int i = 1; i < n; i++)
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    return z;
}

// ---- suffix array + LCP ----
// sa = start indices of the n suffixes in sorted order (no empty suffix, unlike KACTL's n+1 version). O(n^2 log n), n <= 1000   (from KACTL stress-tests/strings/SuffixArray.cpp)
vi suffixArray(const string& s) {
    vi sa(s.size());
    iota(sa.begin(), sa.end(), 0);
    sort(sa.begin(), sa.end(), [&](int a, int b) { return s.substr(a) < s.substr(b); });
    return sa;
}
// lcp[i] = LCP of suffixes sa[i-1] and sa[i], lcp[0] = 0. O(n^2), n <= 1000
vi lcpArray(const string& s, const vi& sa) {
    vi lcp(sa.size());
    for (int i = 1; i < (int)sa.size(); i++)
        while (max(sa[i], sa[i - 1]) + lcp[i] < (int)s.size() && s[sa[i] + lcp[i]] == s[sa[i - 1] + lcp[i]]) lcp[i]++;
    return lcp;
}

// ---- minimum rotation ----
// smallest index i such that s rotated to start at i is lexicographically minimal. O(n^2), n <= 2000   (from KACTL stress-tests/strings/MinRotation.cpp)
int minRotation(const string& s) {
    int best = 0;
    for (int i = 1; i < (int)s.size(); i++)
        if (s.substr(i) + s.substr(0, i) < s.substr(best) + s.substr(0, best)) best = i;
    return best;
}

// ---- rotation check ----
// is t some rotation of s. O(n^2), n <= 2000
bool isRotation(const string& s, const string& t) {
    if (s.size() != t.size()) return false;
    for (int i = 0; i < (int)s.size() || i == 0; i++)
        if (s.substr(i) + s.substr(0, i) == t) return true;
    return false;
}

// ---- smallest period ----
// smallest p >= 1 with s[i] == s[i+p] for all valid i (p = n if no shorter one). O(n^2), n <= 3000; s nonempty
int smallestPeriod(const string& s) {
    for (int p = 1; p < (int)s.size(); p++) {
        bool ok = true;
        for (int i = 0; i + p < (int)s.size(); i++) ok &= s[i] == s[i + p];
        if (ok) return p;
    }
    return s.size();
}

// ---- palindromes ----
bool isPal(const string& s) { return equal(s.begin(), s.begin() + s.size() / 2, s.rbegin()); }
// {start, length} of the longest palindromic substring, leftmost on ties. O(n^3), n <= 200
pii longestPal(const string& s) {
    pii best = {0, 0};
    for (int i = 0; i < (int)s.size(); i++)
        for (int len = 1; i + len <= (int)s.size(); len++)
            if (len > best.second && isPal(s.substr(i, len))) best = {i, len};
    return best;
}
// number of palindromic substrings, counted per (start, end) position pair. O(n^3), n <= 200
ll countPals(const string& s) {
    ll c = 0;
    for (int i = 0; i < (int)s.size(); i++)
        for (int len = 1; i + len <= (int)s.size(); len++) c += isPal(s.substr(i, len));
    return c;
}

// ---- distinct substrings ----
// number of different non-empty substrings. O(n^3 log n), n <= 100
ll distinctSubstrings(const string& s) {
    set<string> st;
    for (int i = 0; i < (int)s.size(); i++)
        for (int len = 1; i + len <= (int)s.size(); len++) st.insert(s.substr(i, len));
    return st.size();
}

// ---- longest common substring ----
// length of the longest string that is a substring of both s and t. O(n*m*min(n,m)), n,m <= 100
int longestCommonSubstring(const string& s, const string& t) {
    int best = 0;
    for (int i = 0; i < (int)s.size(); i++)
        for (int j = 0; j < (int)t.size(); j++) {
            int k = 0;
            while (i + k < (int)s.size() && j + k < (int)t.size() && s[i + k] == t[j + k]) k++;
            best = max(best, k);
        }
    return best;
}

// ---- longest repeated substring ----
// length of the longest substring that occurs at least twice (the two occurrences may overlap). O(n^3), n <= 200
int longestRepeated(const string& s) {
    int best = 0;
    for (int i = 0; i < (int)s.size(); i++)
        for (int j = i + 1; j < (int)s.size(); j++) {
            int k = 0;
            while (j + k < (int)s.size() && s[i + k] == s[j + k]) k++;
            best = max(best, k);
        }
    return best;
}

// ---- count k patterns ----
// c[j] = number of (overlapping) occurrences of pats[j] in s; patterns may repeat. O(k*n*m), Aho-Corasick brute
vi countPatterns(const string& s, const vector<string>& pats) {
    vi c;
    for (const string& t : pats) c.push_back(occurrences(s, t).size());
    return c;
}

// ---- extra: brackets ----
// is s a balanced '(' ')' sequence (counter never negative, ends at 0; empty is balanced). O(n)
bool isBalanced(const string& s) {
    int b = 0;
    for (char c : s) {
        b += c == '(' ? 1 : -1;
        if (b < 0) return false;
    }
    return b == 0;
}
// number of non-empty balanced substrings, counted per (start, length) position pair. O(n^3), n <= 200
ll countBalancedSubstrings(const string& s) {
    ll c = 0;
    for (int i = 0; i < (int)s.size(); i++)
        for (int len = 1; i + len <= (int)s.size(); len++) c += isBalanced(s.substr(i, len));
    return c;
}

int main() { // reads what gen.cpp's default main prints (text line, pattern line); other formats: see gen.cpp
    string s, t;
    cin >> s >> t;
    vi r = occurrences(s, t);
    printf("%d\n", (int)r.size());
    for (int x : r) printf("%d ", x);
    puts("");
    // one string:  cin >> s; prefixFunc(s) / zFunc(s) / suffixArray(s) / minRotation(s) / longestPal(s) / distinctSubstrings(s) / smallestPeriod(s)
    // two strings: cin >> s >> t; longestCommonSubstring(s, t) / isRotation(s, t)
    // k patterns:  cin >> s >> k, then k strings; countPatterns(s, pats)
    // brackets:    cin >> s; isBalanced(s) / countBalancedSubstrings(s)
}

#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}

using int128 = __int128_t;

// --- I/O Functions for 128-bit integers ---

// Overload the << operator to print __int128_t
std::ostream& operator<<(std::ostream& os, int128 val) {
    if (val == 0) return os << "0";
    std::string s = "";
    bool is_negative = false;
    if (val < 0) {
        is_negative = true;
        val = -val;
    }
    while (val > 0) {
        s += (val % 10) + '0';
        val /= 10;
    }
    if (is_negative) {
        s += '-';
    }
    std::reverse(s.begin(), s.end());
    return os << s;
}

// Overload the >> operator to read __int128_t
std::istream& operator>>(std::istream& is, int128& val) {
    std::string s;
    is >> s;
    val = 0;
    bool is_negative = false;
    int start_index = 0;
    if (s[0] == '-') {
        is_negative = true;
        start_index = 1;
    }
    for (int i = start_index; i < (int)s.length(); i++) {
        val = val * 10 + (s[i] - '0');
    }
    if (is_negative) {
        val = -val;
    }
    return is;
}



void solve(int test_case) {
    ull x = 2097151;
    ull a = 2 * x * x * x + x + 10 - 4 * x * x ;
    cout<<a<<ln;
    int128 x1 = 2097151;
    int128 a1 =  2 * x1 * x1 * x1;
    int128 b1 = 4 * x * x;
    int128 c1 = a1 - b1 + x  + 10;
    cout<<a1<<" "<<b1<<" "<<c1<<ln;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

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

const int MOD = 1'000'000'007;
int fp(int x, int y) {
    if(y < 0) return 1;
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % MOD;
        x = 1LL * x * x % MOD;
        y >>= 1;
    }
    return res;
}

void solve(int test_case) {
    int n;
    cin >> n;

    vi v(n);
    cin >> v;

    map<int, int> mp;
    for (int x : v) mp[x]++;

    int res = 1;
    int d = 0;
    int prev = -1;

    for (auto [x, cnt] : mp) {
        if (x == -1) continue;

        res = res * fp(2, cnt - 1) % MOD;

        if (prev != -1 && x - prev == 1)
            d++;

        prev = x;
    }

    int m = mp[-1];

    if (m > 0) {
        res = res * fp(2, m - 1) % MOD;
        res = res * (d + 1) % MOD;
    }

    cout << res << ln;
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
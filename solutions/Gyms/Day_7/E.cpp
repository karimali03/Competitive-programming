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

// Return a mask with the lowest k bits set.
// Examples: k=0 -> 0, k=5 -> 11111. For signed ll, k is capped at 63 bits.
ll lowBitsMask(int k) {
    if (k <= 0) return 0;
    if (k >= 63) return LLONG_MAX;
    return (1LL << k) - 1;
}


ll clearFromZeroThrough(ll x, int i) {
    assert(x >= 0);
    if (i < 0) return x;
    if (i >= 62) return 0;
    return x & ~lowBitsMask(i + 1);
}

void solve(int test_case) {
    int n, q;
    cin >> n >> q;

    vector<ll> v(n);

    for (int i = 0; i < n; i++) {
        ll a; cin >> a;
        v[i] = (a - 1) / 2;
    }

    sort(rall(v));

    auto apply = [&](ll x, int idx) -> ll {
        ll y = v[idx];

        // We may choose remainder = x
        if (y >= x)
            return 0;

        for (int i = 31; i >= 0; i--) {
            int bx = (x >> i) & 1;
            int by = (y >> i) & 1;

            if (!by)
                continue;

            if (bx) {
                x ^= (1LL << i);
            }
            else {
                x = clearFromZeroThrough(x, i);
                break;
            }
        }

        return x;
    };

    while (q--) {
        ll x;
        cin >> x;

        for (int i = 0; i < n && x; i++) {
            ll cur = apply(x, i);

            if (cur == x)
                break;

            x = cur;
        }

        if (x == 0) YES;
        else NO;
    }
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
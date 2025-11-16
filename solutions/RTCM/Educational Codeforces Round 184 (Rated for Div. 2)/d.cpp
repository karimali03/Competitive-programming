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

void solve(int tc) {
    int x, y, k; cin>>x>>y>>k;
    int lim = 1000000000000;

    if (y == 1) {
        NA;
        return;
    }
    // cur = cur + cur/y-1
    int a = y - 1;

    while (x > 0) {
        int q = (k - 1) / a;
        if (q == 0)  break;
        int r = (k - 1) % a; // dis
        int m = (a - r + q - 1) / q;
        m = min(m, x);
        if (q > (lim - k) / m) {
            k = lim + 1;
            break;
        }
        k += m * q;
        x -= m;
    }

    if (k > lim) {
        NA;
    } else {
        cout<<k<<ln;
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
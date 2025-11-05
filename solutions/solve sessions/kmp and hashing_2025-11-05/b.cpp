#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define int long long

const int MOD = 1e9 + 9;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll BASE = uniform_int_distribution<ll>(100000000, 1000000000)(rng) | 1; // random odd base

map<ll,int> hval;
int cnt = 1;
ll mod_pow(ll base, ll exp, ll mod) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

int get(ll x) {
    if (hval.count(x)) return hval[x];
    return hval[x] = mod_pow(BASE, cnt++, MOD);
}

struct MultisetHashing {
    vector<int> h;
    int n;
    MultisetHashing(vector<int> &v) {
        n = v.size();
        h = vector<int>(n + 1);
        for (int i = 0; i < n; i++) {
            (h[i + 1] =  get(v[i]) + h[i])%=MOD;
        }
    }
    int get_hash(int l, int r) {
        int ret = h[r] - h[l-1] + MOD;
        return ret % MOD;
    }
};

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (auto &x : a) cin >> x;
    for (auto &x : b) cin >> x;

    MultisetHashing sa(a), sb(b);
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y;
        if (sa.get_hash(1, x) == sb.get_hash(1, y)) cout << "Yes\n";
        else cout << "No\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
}

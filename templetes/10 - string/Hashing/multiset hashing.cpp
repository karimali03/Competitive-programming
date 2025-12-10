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
    // zero based
    int get_hash(int l, int r) {
        int ret = h[r+1] - h[l] + MOD;
        return ret % MOD;
    }
};

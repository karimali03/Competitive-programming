mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
map<ll,ll> hval;
ll get(ll x) {
    if(hval.count(x)) return hval[x];
    return hval[x] = rng();
}

struct XorHashing {
    vector<int> h;
    int n;
    XorHashing(vector<int> &v) {
        n = v.size();
        h = vector<ll>(n + 1);
        for (int i = 0; i < n; i++) {
            h[i + 1] =  get(v[i]) ^ h[i];
        }
    }
    // zero based
    ll get_hash(int l, int r) {
        return h[r+1] ^ h[l];
    }
};

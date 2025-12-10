struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    void add(int idx, ll val){ // idx is 1..n
        while(idx <= n){
            bit[idx] = (bit[idx] + val) % MOD;
            idx += idx & -idx;
        }
    }
    ll sumPrefix(int idx){ // sum 1..idx
        ll res = 0;
        while(idx > 0){
            res = (res + bit[idx]) % MOD;
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1) + MOD) % MOD;
    }
};

struct Fenwick {
    int n;
    vector<ll> bit;
    Fenwick() : n(0) {}
    Fenwick(int n_){
        n = n_ + 5;
        bit.assign(n+1, 0); // 1-indexed, supports indices 1..n
    }
    // idx is 1..n
    void add(int idx, ll val){ 
        while(idx <= n){
            bit[idx] = (bit[idx] + val);
            idx += idx & -idx;
        }
    }
    // sum 1..idx
    ll sumPrefix(int idx){ 
        ll res = 0;
        while(idx > 0){
            res = (res + bit[idx]);
            idx -= idx & -idx;
        }
        return res;
    }
    // sum on [l..r] with l,r in 1..n
    ll sumRange(int l, int r){
        if(l > r) return 0;
        return (sumPrefix(r) - sumPrefix(l-1));
    }
    // for range update , point query
    // update [l,r] +x  -> add(l,x) , add(r+1,-x) 
    // get idx  -> sumPrefix(idx)
};

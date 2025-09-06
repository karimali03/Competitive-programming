struct FenwickTree{
    static const int N = 1e6+5;
    ll bit[N] {};

    ll merge(int a,int b){
        return a + b;
    }
    // 1 based , add val to idx
    void add(int idx,ll val){
        while( idx < N){
            bit[idx] = merge(bit[idx] , val);
            idx+=idx&-idx;
        }
    }
    // from 1 to idx
    ll query(int idx){
        ll ret=0;
        while(idx>0){
            ret = merge(ret , bit[idx]);
            idx-=idx&-idx;
        }
        return ret;
    }
    // from l to r inclusive 
    ll prefix(int l,int r){
        return query(r)-query(l-1);
    }
};

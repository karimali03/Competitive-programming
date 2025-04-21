const int N = 3'000'01;
const int MOD = 998244353;
int fact[N],inv_fact[N];
int fp(x,y,m){
    int res = 1;
    while(y){
        if(y&1) res = res * x % m;
        y = y * y % m;
        y>>=1;
    }
    return res;
}

void pre_compute(){
    fact[0]  = inv_fact[0] = 1;
    for(int i = 1 ; i < N ; i++) 
    fact[i] = ( i%MOD * fact[i-1]%MOD )% MOD;
    for (int i = 1; i < N; i++) 
    inv_fact[i] = fp(fact[i],MOD-2,MOD);
}
 
int ncr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

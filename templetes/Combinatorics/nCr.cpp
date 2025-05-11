const int N = 1'000'005;
const int MOD = 1'000'000'007;
int fact[N],inv_fact[N];

int fp(int x,int y){
    int res = 1;
    while(y > 0){
        if(y&1) res = res * x % MOD;
        x = x * x % MOD;
        y>>=1;
    }
    return res;
}

void INIT(){
    fact[0]  = inv_fact[0] = 1;
    for(int i = 1 ; i < N ; i++) 
    fact[i] = ( i%MOD * fact[i-1]%MOD )% MOD;
    for (int i = 1; i < N; i++) 
    inv_fact[i] = fp(fact[i],MOD-2);
}
 
int nCr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

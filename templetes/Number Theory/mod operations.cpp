const int MOD = 1000000007;

int add(int a, int b) {
    return ((a % MOD) + (b % MOD)) % MOD;
}

int mul(int a, int b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}

int fp(int a,int b){
    int res = 1;
    while(b > 0){
        if(b&1) res = a * res % MOD;
        a = a * a % MOD;
        b>>=1;
    }
    return res;
}

int modinv(int x){
	return fast_power(x,MOD-2);
}

int divison(int a,int b){
    return mul( a , fast_power(b,MOD-2));
}
int sub(int a, int b) {
    return ((a % MOD) - (b % MOD) + MOD) % MOD;
}

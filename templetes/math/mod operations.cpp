const int mod = 1000000007;

int add(int a, int b) {
    return ((a % mod) + (b % mod)) % mod;
}

int mul(int a, int b) {
    return ((a % mod) * (b % mod)) % mod;
}

int fast_power(int a,int b){
    int res=1;
    while(b > 0){
        if(b&1) res = mul(a,res);
        a =mul(a,a);
        b/=2;
    }

    return res;
}

int modinv(int x , int m){
	return fast_power(x,m-2);
}

int divison(int a,int b){
    return mul( a , fast_power(b,mod-2));
}
int sub(int a, int b) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

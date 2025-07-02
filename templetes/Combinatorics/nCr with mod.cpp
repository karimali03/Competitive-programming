const int N = 1'000'005;
const int MOD = 1'000'000'007;
int fact[N], inv_fact[N];

int fp(int x, int y) {
    int res = 1;
    while (y > 0) {
        if (y & 1) res = 1LL * res * x % MOD;
        x = 1LL * x * x % MOD;
        y >>= 1;
    }
    return res;
}

void INIT() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < N; i++) 
        fact[i] = 1LL * i * fact[i - 1] % MOD;
    for (int i = 1; i < N; i++) 
        inv_fact[i] = fp(fact[i], MOD - 2);
}

int nCr(int n, int k) {
    if (n < k || k < 0) return 0;
    return 1LL * fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

int nPr(int n, int r) {
    if (n < r || r < 0) return 0;
    return 1LL * fact[n] * inv_fact[n - r] % MOD;
}

int catalan(int n) {
    if (n == 0) return 1;
    int res = nCr(2 * n, n);
    res = 1LL * res * fp(n + 1, MOD - 2) % MOD;
    return res;
}

// Stars and Bars: number of ways to divide n identical items into k parts (with empty parts)
int starsAndBars(int n, int k) {
    if (n < 0 || k <= 0) return 0;
    return nCr(n + k - 1, k - 1);
}


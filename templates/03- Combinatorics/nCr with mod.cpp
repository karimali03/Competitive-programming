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

// 1. Identical balls, distinct boxes, empty allowed
int starsAndBars(int balls, int boxes) {
    if (balls < 0 || boxes <= 0) return 0;
    return nCr(balls + boxes - 1, boxes - 1);
}

// 2. Identical balls, distinct boxes, NO empty boxes
int starsAndBarsNoEmpty(int balls, int boxes) {
    if (balls < boxes || boxes <= 0) return 0;
    return nCr(balls - 1, boxes - 1);
}

// 3. Identical balls, distinct boxes, each box gets AT LEAST L balls
int starsAndBarsLowerBound(int balls, int boxes, int L) {
    int adjusted = balls - L * boxes;
    if (adjusted < 0) return 0;
    return nCr(adjusted + boxes - 1, boxes - 1);
}

// 4. Identical balls, distinct boxes, each box gets [L, R] balls (harder)
int starsAndBarsBounds(int balls, int boxes, int L, int R) {
    // Inclusion-exclusion over max bound R
    int res = 0;
    for (int i = 0; i <= boxes; i++) {
        int sign = (i & 1) ? -1 : 1;
        int val = balls - boxes * L - i * (R - L + 1);
        if (val < 0) break;
        int ways = 1LL * nCr(boxes, i) * nCr(val + boxes - 1, boxes - 1) % MOD;
        res = (res + sign * ways + MOD) % MOD;
    }
    return res;
}



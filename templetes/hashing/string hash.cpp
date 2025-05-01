const int P = 41;
// safe_primes = {31, 37, 41, 53, 59, 67, 71, 79, 89, 97}; 
const int M = 1e9 + 9;
const int MAXN = 1e6 + 5;
int p_pow[MAXN], inv_p_pow[MAXN];

// Fast modular exponentiation
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Precompute powers and inverses
void INIT() {
    p_pow[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p_pow[i] = p_pow[i - 1] * P % M;
    }
    for (int i = 0; i < MAXN; i++) {
        inv_p_pow[i] = mod_pow(p_pow[i], M - 2, M);
    }
}


struct StringHasher {
    vector<long long> hash;

    StringHasher(const string &s) {
        int n = s.size();
        hash.resize(n + 1, 0);
        for (int i = 0; i < n; i++) {
            hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * p_pow[i]) % M;
        }
    }

    long long get_hash(int l, int r) {
        long long h = (hash[r + 1] - hash[l] + M) % M;
        return h * inv_p_pow[l] % M;
    }
};

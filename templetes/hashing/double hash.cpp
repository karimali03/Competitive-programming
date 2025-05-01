
// Constants
const int MAXN = 2e5 + 5;
const int M1 = 1e9 + 7, M2 = 1e9 + 9;
const int P1 = 54, P2 = 37;

// Precomputed arrays
int p_pow1[MAXN], inv_p_pow1[MAXN];
int p_pow2[MAXN], inv_p_pow2[MAXN];

// Modular exponentiation (Fermat's little theorem for inverse)
long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    while (exp) {
        if (exp & 1) res = res * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return res;
}

// Precompute powers and modular inverses
void INIT() {
    p_pow1[0] = p_pow2[0] = 1;
    for (int i = 1; i < MAXN; i++) {
        p_pow1[i] = p_pow1[i - 1] * P1 % M1;
        p_pow2[i] = p_pow2[i - 1] * P2 % M2;
    }
    for (int i = 0; i < MAXN; i++) {
        inv_p_pow1[i] = mod_pow(p_pow1[i], M1 - 2, M1);
        inv_p_pow2[i] = mod_pow(p_pow2[i], M2 - 2, M2);
    }
}

// Double Hashing Struct
struct DoubleHasher {
    vector<long long> hash1, hash2;

    DoubleHasher(const string &s) {
        int n = s.size();
        hash1.resize(n + 1, 0);
        hash2.resize(n + 1, 0);

        for (int i = 0; i < n; i++) {
            hash1[i + 1] = (hash1[i] + (s[i] - 'a' + 1) * p_pow1[i]) % M1;
            hash2[i + 1] = (hash2[i] + (s[i] - 'a' + 1) * p_pow2[i]) % M2;
        }
    }

    // Get hash of substring [l..r]
    pair<long long, long long> get_hash(int l, int r) {
        long long h1 = (hash1[r + 1] - hash1[l] + M1) % M1;
        h1 = h1 * inv_p_pow1[l] % M1;

        long long h2 = (hash2[r + 1] - hash2[l] + M2) % M2;
        h2 = h2 * inv_p_pow2[l] % M2;

        return {h1, h2};
    }
};

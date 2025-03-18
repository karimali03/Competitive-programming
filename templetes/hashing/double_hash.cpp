#include <bits/stdc++.h>
using namespace std;

#define int long long

struct DoubleHasher {
	// safe_primes = {31, 37, 41, 53, 59, 67, 71, 79, 89, 97}; 
    int P1 = 54, P2 = 37;
    static const int M1 = 1e9 + 7, M2 = 1e9 + 9;

    vector<long long> hash1, hash2, p_pow1, p_pow2, inv_p_pow1, inv_p_pow2;

    // Modular exponentiation to compute modular inverse
    long long mod_inv(long long base, long long mod) {
        long long result = 1, exp = mod - 2;
        while (exp) {
            if (exp % 2) result = (result * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }

    DoubleHasher(const string &s) {
        int n = s.size();
        hash1.resize(n + 1, 0), hash2.resize(n + 1, 0);
        p_pow1.resize(n + 1, 1), p_pow2.resize(n + 1, 1);
        inv_p_pow1.resize(n + 1, 1), inv_p_pow2.resize(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            p_pow1[i] = (p_pow1[i - 1] * P1) % M1;
            p_pow2[i] = (p_pow2[i - 1] * P2) % M2;
            inv_p_pow1[i] = mod_inv(p_pow1[i], M1);
            inv_p_pow2[i] = mod_inv(p_pow2[i], M2);
        }

        for (int i = 0; i < n; i++) {
            hash1[i + 1] = (hash1[i] + (s[i] - 'a' + 1) * p_pow1[i]) % M1;
            hash2[i + 1] = (hash2[i] + (s[i] - 'a' + 1) * p_pow2[i]) % M2;
        }
    }

    // Get double hash of substring s[l...r] (0-based) using modular inverse
    pair<long long, long long> get_hash(int l, int r) {
        long long h1 = (hash1[r + 1] - hash1[l] + M1) % M1;
        h1 = (h1 * inv_p_pow1[l]) % M1; // Use modular inverse

        long long h2 = (hash2[r + 1] - hash2[l] + M2) % M2;
        h2 = (h2 * inv_p_pow2[l]) % M2;

        return {h1, h2};
    }
};

void solve(int test_case) {
    string a, b;
    cin >> a >> b;
    
    DoubleHasher sh(a), sh2(b);
    int cnt = 0;

    for (int i = 0; i <= (int)a.size() - (int)b.size(); i++) {
        if (sh2.get_hash(0, (int)b.size() - 1) == sh.get_hash(i, i + (int)b.size() - 1)) {
            cnt++;
        }
    }

    cout << cnt << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = 1;
    // cin >> t;
    
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}

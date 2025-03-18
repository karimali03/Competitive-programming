#include <bits/stdc++.h>
using namespace std;
 
struct StringHasher {
    
    // safe_primes = {31, 37, 41, 53, 59, 67, 71, 79, 89, 97}; 
    static const int P = 54;           // Prime base for hashing
    static const int M = 1e9 + 9;      // Large prime modulus
    vector<long long> hash, p_pow, inv_p_pow;
 
    // Compute modular inverse using Fermat’s theorem
    long long mod_inv(long long base, long long mod) {
        long long result = 1, exp = mod - 2;
        while (exp) {
            if (exp % 2) result = (result * base) % mod;
            base = (base * base) % mod;
            exp /= 2;
        }
        return result;
    }
 
    StringHasher(const string &s) {
        int n = s.size();
        hash.resize(n + 1, 0); // Prefix hash array
        p_pow.resize(n + 1, 1); // Powers of P
        inv_p_pow.resize(n + 1, 1); // Modular inverses of p_pow
 
        for (int i = 1; i <= n; i++) {
            p_pow[i] = (p_pow[i - 1] * P) % M;
            inv_p_pow[i] = mod_inv(p_pow[i], M);
        }
 
        for (int i = 0; i < n; i++)
            hash[i + 1] = (hash[i] + (s[i] - 'a' + 1) * p_pow[i]) % M;
    }
 
    // Get hash of substring s[l...r] (0-based)
    long long get_hash(int l, int r) {
        long long h = (hash[r + 1] - hash[l] + M) % M;
        return (h * inv_p_pow[l]) % M; // Normalize using modular inverse
    }
};
 
 
long long compute_hash(string const& s) {
    const int p = 43;
    const int m = 1e9 + 9;
    long long hash_value = 0;
    long long p_pow = 1;
    for (char c : s) {
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}
 
 
int main() {
    string a,b; cin>>a>>b;
    StringHasher sh(a);
    int hash = compute_hash(b);
    int cnt = 0;
    for(int  i = 0 ; i <= (int)a.size()-(int)b.size() ; i++){
        if(hash == sh.get_hash(i,i+(int)b.size()-1)) cnt++;
    }
 
    cout<<cnt;
 
}
- Suppose a is an integer and b is a positive integer. Then there exist unique integers
q and r such that 0 ≤ r < b and  a = bq + r.
- a ≡ b (mod m) if and only if a – b is divisible by m.
if a = mp + r and b = mq + r then a – b = m(p – q).
- If a ≡ b (mod m) and c ≡ d (mod m) then a + c ≡ b + d (mod m).
- If a ≡ b (mod m) and c ≡ d (mod m) then ac ≡ bd (mod m).
- If a ≡ b (mod m) then a^n ≡ b^n (mod m).
- If ka ≡ kb (mod m) and gcd(k, m) = 1 then a ≡ b (mod m).
- Fermat’s Little Theorem
Let a be an integer and p be a prime such that gcd(a, p) = 1. Then  a^(p-1) ≡ 1 (mod p).
- Let gcd(m, n) = 1. Then the numbers m, 2m, 3m, ..., nm give different residues modulo n.


// Finds an integer K (2 <= K <= M) that maximizes (Y % K)
// Returns the maximum possible remainder.
long long maximize_modulo(long long Y, long long M) {
    if (M < 2) return -1; // No valid K exists
    
    // If the limit M is greater than Y, we can just pick K = Y + 1
    // to get a remainder of exactly Y.
    if (Y < M) {
        return Y; // (Y % (Y + 1) == Y)
    }
    
    // Otherwise, use the optimal boundary formula
    long long c = Y / M;
    long long best_k = Y / (c + 1) + 1;
    
    return Y % best_k;
}


// count numbers from 0 to limit where num % mod = rem
int count(int mod,int rem,int limit){
    if(limit < rem) return 0;
    return (limit-rem) / mod + 1;
}

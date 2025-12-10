// Function to safely calculate (a * b) % m without overflow.
// This is necessary when a, b, and m are close to the long long limit.
long long modular_multiply(long long a, long long b, long long m) {
    long long result = 0;
    a %= m;
    while (b > 0) {
        // If b is odd, add a to the result
        if (b % 2 == 1) {
            result = (result + a) % m;
        }
        // Double a and halve b
        a = (a * 2) % m;
        b /= 2;
    }
    return result;
}

// Function to find the Extended GCD of a and b
long long extendedGcd(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long gcd = extendedGcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

// Function to solve a system of congruences using the Chinese Remainder Theorem.
// Returns {-1, -1} if no solution exists.
std::pair<long long, long long> crt(const std::vector<long long>& a, const std::vector<long long>& m) {
    if (a.empty() || m.empty()) {
        return {0, 1};
    }

    long long current_a = a[0];
    long long current_m = m[0];

    for (size_t i = 1; i < a.size(); ++i) {
        long long next_a = a[i];
        long long next_m = m[i];
        
        long long x, y;
        long long g = extendedGcd(current_m, next_m, x, y);

        long long diff = next_a - current_a;
        
        if (diff % g != 0) {
            return {-1, -1};
        }

        // WARNING: This is the line that can overflow if the LCM is too large.
        long long new_m = (current_m / g) * next_m;
        
        long long mod_for_k = next_m / g;
        long long k_part1 = (diff % next_m + next_m) % next_m / g;
        long long inv_x = (x % mod_for_k + mod_for_k) % mod_for_k;

        long long k = modular_multiply(k_part1, inv_x, mod_for_k);

        long long term_to_add = modular_multiply(k, current_m, new_m);
        current_a = (current_a + term_to_add) % new_m;
        
        current_m = new_m;
        current_a = (current_a + current_m) % current_m;
    }

    return {current_a, current_m};
}

using int128 = __int128_t;

// Helper function to print 128-bit integers
std::ostream& operator<<(std::ostream& os, int128 val) {
    if (val == 0) return os << "0";
    std::string s = "";
    bool neg = val < 0;
    if (neg) val = -val;
    while (val > 0) {
        s += (val % 10) + '0';
        val /= 10;
    }
    if (neg) s += '-';
    std::reverse(s.begin(), s.end());
    return os << s;
}

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

std::pair<long long, long long> crt(const std::vector<long long>& a, const std::vector<long long>& m) {
    if (a.empty() || m.empty()) {
        return {0, 1};
    }

    int128 current_a = a[0];
    int128 current_m = m[0];

    for (size_t i = 1; i < a.size(); ++i) {
        int128 next_a = a[i];
        int128 next_m = m[i];
        
        // These two variables were missing their declaration.
        long long x, y; 
        long long g = extendedGcd(current_m, next_m, x, y);

        int128 diff = next_a - current_a;
        
        if (diff % g != 0) {
            return {-1, -1};
        }

        int128 new_m = (current_m / g) * next_m;
        // The x from extendedGcd is the modular inverse we need.
        int128 k = diff / g * x; 
        
        current_a = current_a + k * current_m;
        
        current_m = new_m;
        current_a = (current_a % current_m + current_m) % current_m;
    }

    return {(long long)current_a, (long long)current_m};
}


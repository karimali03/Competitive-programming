// Function to find the Extended GCD of a and b
// It also finds coefficients x and y such that: ax + by = gcd(a, b)
long long extendedGcd(long long a, long long b, long long &x, long long &y) {
    // Base case
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }

    long long x1, y1; // To store results of the recursive call
    long long gcd = extendedGcd(b % a, a, x1, y1);

    // Update x and y using results of the recursive call
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

// Function to find the modular inverse of a modulo m
long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extendedGcd(a, m, x, y);

    // The inverse doesn't exist if a and m are not relatively prime
    if (g != 1) {
        return -1;
    }

    // The modular inverse is x, but we want the smallest positive value
    // (x % m + m) % m handles both positive and negative x
    return (x % m + m) % m;
}

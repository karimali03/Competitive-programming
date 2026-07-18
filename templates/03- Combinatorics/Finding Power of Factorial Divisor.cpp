// Given two integers n and k, compute the maximum value of x such that k^x divides n!
// That is, find the largest x such that (k^x) | n!

// bigest x such that prime p^x divides !n
int legendre(int n, int p) {  // logk(n)
    int exponent = 0;
    while (n) {
        n /= p;
        exponent += n;
    }
    return exponent;
}


// Function to factorize k into its prime components
map<int, int> factorize(int k) {
    map<int, int> factors;
    for (int i = 2; i * i <= k; ++i) {
        while (k % i == 0) {
            ++factors[i];
            k /= i;
        }
    }
    if (k > 1) {
        ++factors[k];
    }
    return factors;
}

// Function to compute the exponent of k in n!
int exponent_in_factorial(int n, int k) {
    map<int, int> factors = factorize(k);
    int min_exp = INT_MAX;
    for (const auto& [prime, count] : factors) {
        int exp = legendre(n, prime) / count;
        min_exp = std::min(min_exp, exp);
    }
    return min_exp;
}
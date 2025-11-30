// Sum from 1 to n: n * (n + 1) / 2
long long sum1ToN(int n) {
    return 1LL * n * (n + 1) / 2;
}

// Sum of squares: n(n + 1)(2n + 1) / 6
long long sumSquares(int n) {
    return 1LL * n * (n + 1) * (2 * n + 1) / 6;
}

// Sum of cubes: [n(n + 1)/2]^2
long long sumCubes(int n) {
    long long s = 1LL * n * (n + 1) / 2;
    return s * s;
}

// Sum of first n odd numbers: n^2
int sumOdd(int n) {
    return n * n;
}

// Sum of first n even numbers: n(n + 1)
int sumEven(int n) {
    return n * (n + 1);
}

// Sum of arithmetic progression: n/2 * [2a + (n-1)d]
long long sumAP(int a, int d, int n) {
    return 1LL * n * (2 * a + (n - 1) * d) / 2;
}

// Sum of geometric progression: a * (r^n - 1) / (r - 1)
long long sumGP(int a, int r, int n) {
    if (r == 1) return 1LL * a * n;
    return 1LL * a * (pow(r, n) - 1) / (r - 1);
}

// Approximate harmonic sum: ln(n) + γ (Euler–Mascheroni constant ≈ 0.577)
double harmonicSum(int n) {
    return log(n) + 0.5772156649;
}

// Stirling's approximation: log(n!) ≈ n log n - n
double logFactorial(int n) {
    return n * log(n) - n;
}

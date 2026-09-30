const int N = 1e6 + 5;
const int MOD = 1e9 + 7;

long long der[N];

// der[n] = number of permutations of n elements
// where no element stays in its original position.
// This is called a derangement.
//
// Base cases:
// der[0] = 1
// der[1] = 0
//
// Recurrence:
// der[n] = (n - 1) * (der[n - 1] + der[n - 2])

void init_derangement() {
    der[0] = 1;
    der[1] = 0;

    for (int i = 2; i < N; i++) {
        der[i] = 1LL * (i - 1) * (der[i - 1] + der[i - 2]) % MOD;
    }
}

// The number of dimensions (e.g., 6 digits)
const int DIMS = 6;
// The base of each dimension (e.g., 10 for digits 0-9)
const int BASE = 10;
// The total number of states (BASE^DIMS)
const int MX = 1000000; // 10^6

// Helper array to store powers of BASE (BASE^0, BASE^1, ...)
long long p_base[DIMS];

// Call this once in main() to initialize p_base
void init_base_powers() {
    p_base[0] = 1;
    for (int i = 1; i < DIMS; i++) {
        p_base[i] = p_base[i - 1] * BASE;
    }
}

/**
 * @brief Computes Sum Over Subsets for a base-b system.
 * After this, dp[mask] = sum(initial[sub]) for all sub <= mask.
 * This is a multi-dimensional prefix sum.
 * @param dp The DP array to transform.
 */
void SOS_subsets(std::vector<long long>& dp) {
    // Iterate over each dimension (digit)
    for (int d = 0; d < DIMS; d++) {
        // Iterate over all masks from low to high
        for (int mask = 0; mask < MX; mask++) {
            // Get the k-th digit of the current mask
            int digit = (mask / p_base[d]) % BASE;
            
            // If the digit is > 0, add the value from the "neighbor"
            // with a smaller digit (k-1)
            if (digit > 0) {
                int neighbor = mask - p_base[d];
                // dp[k] += dp[k-1]
                dp[mask] = add(dp[mask], dp[neighbor]);
            }
        }
    }
}

/**
 * @brief Reverses the Sum Over Subsets operation (Inverse SOS).
 * This is the base-b version of your REV1.
 * @param dp The DP array to transform.
 */
void Inverse_SOS_subsets(std::vector<long long>& dp) {
    // Iterate over each dimension (digit)
    for (int d = 0; d < DIMS; d++) {
        // Iterate over all masks from high to low
        for (int mask = MX - 1; mask >= 0; mask--) {
            int digit = (mask / p_base[d]) % BASE;
            
            if (digit > 0) {
                int neighbor = mask - p_base[d];
                // dp[k] -= dp[k-1]
                dp[mask] = sub(dp[mask], dp[neighbor]);
            }
        }
    }
}

/**
 * @brief Computes Sum Over Supersets for a base-b system.
 * After this, dp[mask] = sum(initial[super]) for all super >= mask.
 * This is a multi-dimensional suffix sum.
 * @param dp The DP array to transform.
 */
void SOS_supersets(std::vector<long long>& dp) {
    // Iterate over each dimension (digit)
    for (int d = 0; d < DIMS; d++) {
        // Iterate over all masks from high to low
        for (int mask = MX - 1; mask >= 0; mask--) {
            int digit = (mask / p_base[d]) % BASE;
            
            // If digit is not the max (e.g., < 9), add from the
            // neighbor with a larger digit (k+1)
            if (digit < BASE - 1) {
                int neighbor = mask + p_base[d];
                // dp[k] += dp[k+1]
                dp[mask] = add(dp[mask], dp[neighbor]);
            }
        }
    }
}

/**
 * @brief Reverses the Sum Over Supersets operation (Inverse SOS).
 * This is the base-b version of your REV2.
 * @param dp The DP array to transform.
 */
void Inverse_SOS_supersets(std::vector<long long>& dp) {
    // Iterate over each dimension (digit)
    for (int d = 0; d < DIMS; d++) {
        // Iterate over all masks from low to high
        for (int mask = 0; mask < MX; mask++) {
            int digit = (mask / p_base[d]) % BASE;
            
            if (digit < BASE - 1) {
                int neighbor = mask + p_base[d];
                // dp[k] -= dp[k+1]
                dp[mask] = sub(dp[mask], dp[neighbor]);
            }
        }
    }
}

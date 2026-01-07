#include <iostream>
#include <vector>

// Define common macros and type aliases used in the image
#define fr(i, n) for (int i = 0; i < (n); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using lli = long long int;

// Constants from the image
const lli MLOG = 20;
const lli MAXN = (1 << MLOG);

/**
 * @brief Sum over Supersets (SOS) DP.
 * dp[mask] = sum(a[i]) for all i such that (i | mask) == i
 * (i.e., mask is a submask of i, or i is a superset of mask)
 */
void forward1(lli dp[]) { // adding element to all its supersets
    fr(bit, MLOG) {
        fr(i, MAXN) {
            if (i & (1 << bit)) {
                dp[i] += dp[i ^ (1 << bit)];
            }
        }
    }
}

/**
 * @brief Reverses the forward1 transform (Inclusion-Exclusion).
 * Used to recover the original array 'a' from the SOS DP array 'dp'.
 */
void backward1(lli dp[]) { // undoes forward1
    fr(bit, MLOG) {
        per(i, MAXN - 1, 0) {
            if (i & (1 << bit)) {
                dp[i] -= dp[i ^ (1 << bit)];
            }
        }
    }
}

/**
 * @brief Sum over Subsets (SOS) DP.
 * dp[mask] = sum(a[i]) for all i such that (i & mask) == i
 * (i.e., i is a submask of mask)
 */
void forward2(lli dp[]) { // add elements to its subsets
    fr(bit, MLOG) {
        per(i, MAXN - 1, 0) {
            if (i & (1 << bit)) {
                dp[i ^ (1 << bit)] += dp[i];
            }
        }
    }
}

/**
 * @brief Reverses the forward2 transform (Inclusion-Exclusion).
 * Used to recover the original array 'a' from the subset sum DP array 'dp'.
 */
void backward2(lli dp[]) { // undoes forward2
    fr(bit, MLOG) {
        fr(i, MAXN) {
            if (i & (1 << bit)) {
                dp[i ^ (1 << bit)] -= dp[i];
            }
        }
    }
}

// Example usage (optional, to make the code runnable)
int main() {
    // Allocate dp array dynamically to avoid stack overflow
    lli* dp = new lli[MAXN];

    // Initialize dp array (e.g., with some values)
    fr(i, MAXN) {
        dp[i] = i; // Example initialization
    }

    std::cout << "Original dp[5]: " << dp[5] << std::endl;
    std::cout << "Original dp[7]: " << dp[7] << std::endl;

    // Perform Sum over Supersets
    forward1(dp);
    
    // dp[5] (0101) should now include contributions from its supersets
    // like 7 (0111), 13 (1101), 15 (1111), etc. (within the MLOG bits)
    // Actually, it adds values from its submasks *up* to supersets.
    // dp[mask] will sum a[submask] for all submasks. Let's trace for dp[7]
    // dp[7] = a[7] + a[6] + a[5] + a[4] + a[3] + a[2] + a[1] + a[0] (if 7 is 111)
    // The comments in the code are slightly confusing.
    // forward1: dp[i] = sum(a[j]) where j is a submask of i.
    // forward2: dp[i] = sum(a[j]) where i is a submask of j.

    std::cout << "After forward1 dp[7]: " << dp[7] << std::endl; // Should be sum 0..7

    // Revert the operation
    backward1(dp);

    std::cout << "After backward1 dp[5]: " << dp[5] << std::endl; // Should be 5
    std::cout << "After backward1 dp[7]: " << dp[7] << std::endl; // Should be 7

    // Clean up dynamic memory
    delete[] dp;

    return 0;
}
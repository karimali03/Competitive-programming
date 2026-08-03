// XOR linear basis for nonnegative ll values.
// Use it for subset-XOR reachability, maximum XOR, and dependency detection.
struct XorBasis {
    static const int BITS = 63;

    // basis[i] is 0 or has highest set bit i.
    ll basis[BITS]{};
    int rankValue = 0;
    int insertedValue = 0;

    // Insert x into the basis.
    // Returns true if x was independent and increased the rank.
    bool insert(ll x) {
        assert(x >= 0);
        ++insertedValue;
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (((x >> bit) & 1LL) == 0) continue;
            if (basis[bit] == 0) {
                basis[bit] = x;
                ++rankValue;
                return true;
            }
            x ^= basis[bit];
        }
        return false;
    }

    // Return true if x can be formed by XORing some inserted subset.
    // Use for target reachability questions.
    bool canMake(ll x) const {
        assert(x >= 0);
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (((x >> bit) & 1LL) == 0) continue;
            if (basis[bit] == 0) return false;
            x ^= basis[bit];
        }
        return true;
    }

    // Return the maximum subset XOR, optionally starting from an existing value.
    // Use for maximum XOR obtainable from any subset.
    ll maxXor(ll start = 0) const {
        assert(start >= 0);
        ll ans = start;
        for (int bit = BITS - 1; bit >= 0; --bit) {
            ans = max(ans, ans ^ basis[bit]);
        }
        return ans;
    }

    // Return the number of independent vectors.
    // Distinct subset XOR values are 2^rank().
    int rank() const {
        return rankValue;
    }

    // Return true if a nonempty subset has XOR 0.
    // This means at least one inserted value was dependent.
    bool hasNonEmptyZeroSubset() const {
        return rankValue < insertedValue;
    }

    // Return number of distinct subset XOR values, capped at LLONG_MAX.
    // Exact answer is 2^rank and only overflows ll when rank >= 63.
    ll distinctValueCount() const {
        if (rankValue >= 63) return LLONG_MAX;
        return 1LL << rankValue;
    }
};

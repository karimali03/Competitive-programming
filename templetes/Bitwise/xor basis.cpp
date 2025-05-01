// Use XOR Basis when:
// 1. You are allowed to XOR subsets of given values (e.g., toggle, flip, or combine elements)
// 2. You need to check if a target value/vector can be formed using XORs
// 3. You're trying to count how many distinct values can be formed by XORs
// 4. You're given operations that are reversible via XOR (flip i and j, toggle paths, etc.)
// 5. You want the minimal representation of reachable XOR values

struct XorBasis {
    static const int BITS = 64; // use 30 for 1e9 values, 64 for full long long
    long long basis[BITS] = {}; // basis[i] has the vector with i-th bit as the highest set

    // Insert a number into the basis
    void insert(long long x) {
        for (int i = BITS - 1; i >= 0; --i) {
            if (!(x & (1LL << i))) continue;
            if (!basis[i]) {
                basis[i] = x;
                return;
            }
            x ^= basis[i];
        }
    }

    // Check if a number can be formed from the basis
    bool canMake(long long x) {
        for (int i = BITS - 1; i >= 0; --i) {
            if (x & (1LL << i)) {
                if (!basis[i]) return false;
                x ^= basis[i];
            }
        }
        return true;
    }

    // Optional: Get the size of the basis (how many independent vectors)
    int size() {
        int res = 0;
        for (int i = 0; i < BITS; ++i)
            res += (basis[i] != 0);
        return res;
    }
};


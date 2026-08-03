// Return true if bit i of x is 1.
// Use this for direct mask membership checks. Valid for nonnegative ll values:
// 0 <= i < 63, because 1LL << 63 is not safe for signed integers.
bool getBit(ll x, int i) {
    assert(0 <= i && i < 63);
    return (x & (1LL << i)) != 0;
}

// Return x after setting bit i to 1.
// Use when adding an element to a bitmask/set representation.
ll setBit(ll x, int i) {
    assert(0 <= i && i < 63);
    return x | (1LL << i);
}

// Return x after clearing bit i to 0.
// Use when removing an element from a bitmask/set representation.
ll clearBit(ll x, int i) {
    assert(0 <= i && i < 63);
    return x & ~(1LL << i);
}

// Return x after toggling bit i.
// Use for flip/toggle operations where applying the same operation twice cancels.
ll flipBit(ll x, int i) {
    assert(0 <= i && i < 63);
    return x ^ (1LL << i);
}

// Return x after assigning bit i to value.
// Use when the new bit value is known as a bool.
ll updateBit(ll x, int i, bool value) {
    return value ? setBit(x, i) : clearBit(x, i);
}

// Count set bits in x.
// Use for mask sizes, parity checks, and combinatorics over subsets.
int popcount(ll x) {
    assert(x >= 0);
    return __builtin_popcountll((unsigned long long)x);
}

// Return the least significant set bit as a mask.
// Example: 1011000 -> 0001000. Returns 0 if x == 0.
ll lowbit(ll x) {
    assert(x >= 0);
    return x & -x;
}

// Return the index of the least significant set bit.
// Use when iterating set bits. Returns -1 if x == 0.
int leastSignificantBitIndex(ll x) {
    assert(x >= 0);
    return x == 0 ? -1 : __builtin_ctzll((unsigned long long)x);
}

// Return the index of the most significant set bit.
// Use for log2-like logic and greedy bit decisions. Returns -1 if x == 0.
int mostSignificantBitIndex(ll x) {
    assert(x >= 0);
    return x == 0 ? -1 : 63 - __builtin_clzll((unsigned long long)x);
}

// Return x after removing its lowest set bit.
// Repeating this is Kernighan's O(number of set bits) popcount loop.
ll removeLowestSetBit(ll x) {
    assert(x >= 0);
    return x & (x - 1);
}

// Return true if x is a positive power of two.
// Use for single-bit masks and divisibility-by-power-of-two checks.
bool isPowerOfTwo(ll x) {
    return x > 0 && (x & (x - 1)) == 0;
}

// Swap every adjacent pair of bits through bit 61 and keep bit 62 unchanged.
// Use for problems that explicitly ask for adjacent bit-pair swapping.
ll swapAdjacentBits(ll x) {
    assert(x >= 0);
    const ll EVEN_BITS = 0x1555555555555555LL; // bits 0,2,4,...,60
    const ll ODD_BITS = 0x2AAAAAAAAAAAAAAALL;  // bits 1,3,5,...,61
    const ll TOP_BIT = 1LL << 62;
    return ((x & ODD_BITS) >> 1) | ((x & EVEN_BITS) << 1) | (x & TOP_BIT);
}

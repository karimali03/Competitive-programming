// Return a mask with the lowest k bits set.
// Examples: k=0 -> 0, k=5 -> 11111. For signed ll, k is capped at 63 bits.
ll lowBitsMask(int k) {
    if (k <= 0) return 0;
    if (k >= 63) return LLONG_MAX;
    return (1LL << k) - 1;
}

// Extract the inclusive bit range [left, right] and move it down to bit 0.
// Use when a problem packs several fields inside one integer.
ll extractRange(ll x, int left, int right) {
    assert(x >= 0);
    assert(0 <= left && left <= right && right < 63);
    return (x >> left) & lowBitsMask(right - left + 1);
}

// Clear bits [0, i], leaving bits above i unchanged.
// Use when you need to round a mask down to a multiple of 2^(i+1).
ll clearFromZeroThrough(ll x, int i) {
    assert(x >= 0);
    if (i < 0) return x;
    if (i >= 62) return 0;
    return x & ~lowBitsMask(i + 1);
}

// Clear bits [i, 62], leaving only bits [0, i-1].
// Use when keeping the suffix below a chosen bit.
ll clearFromIThroughMSB(ll x, int i) {
    assert(x >= 0);
    if (i <= 0) return 0;
    if (i >= 63) return x;
    return x & lowBitsMask(i);
}

// Return true if every set bit in sub also exists in superMask.
// Use when masks represent sets and you need sub is contained in super.
bool isSubmask(ll sub, ll superMask) {
    assert(sub >= 0 && superMask >= 0);
    return (sub & superMask) == sub;
}

// Return true if a and b have no common set bit.
// Use when two chosen subsets must not overlap.
bool areDisjoint(ll a, ll b) {
    assert(a >= 0 && b >= 0);
    return (a & b) == 0;
}

/*
Set operations when masks represent sets:
    union             A | B
    intersection      A & B
    symmetric diff    A ^ B
    A minus B         A & ~B

Useful transformations:
    x | (x - 1)       set every bit below the lowest set bit
    x & (x - 1)       clear the lowest set bit
    x & -x            isolate the lowest set bit
    x & 1             test whether x is odd
    1LL << k          2^k, valid for 0 <= k < 63
    x << k            x * 2^k, if it fits
    x >> k            floor(x / 2^k) for nonnegative x

C++20 <bit> also has useful helpers for unsigned integers:
    has_single_bit, bit_width, bit_floor, bit_ceil, rotl, rotr
*/

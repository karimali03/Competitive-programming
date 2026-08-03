// Return a mask with the lowest k bits set.
// Local copy so this file can be pasted alone.
ll lowBitsMask(int k) {
    if (k <= 0) return 0;
    if (k >= 63) return LLONG_MAX;
    return (1LL << k) - 1;
}

// Return true if sub is a submask of mask.
// Use when masks represent sets and all chosen bits must come from mask.
bool isSubmask(ll sub, ll mask) {
    assert(sub >= 0 && mask >= 0);
    return (sub & mask) == sub;
}

// Count submasks s of mask satisfying 0 <= s <= limit.
// Use when enumerating all submasks is too slow. Returns LLONG_MAX if the exact
// answer does not fit in ll.
ll countSubmasksAtMost(ll mask, ll limit) {
    assert(mask >= 0 && limit >= 0);

    ll ans = 0;
    for (int bit = 62; bit >= 0; --bit) {
        bool limitBit = (limit >> bit) & 1LL;
        bool maskBit = (mask >> bit) & 1LL;

        if (!limitBit) continue;

        int freeBits = __builtin_popcountll((unsigned long long)(mask & lowBitsMask(bit)));
        if (freeBits >= 63) return LLONG_MAX;
        ll add = 1LL << freeBits;
        if (LLONG_MAX - ans < add) return LLONG_MAX;
        ans += add;

        if (!maskBit) return ans;
    }

    return ans == LLONG_MAX ? LLONG_MAX : ans + 1;
}

// Return the binary-reflected Gray code of index.
// Use when consecutive masks must differ by exactly one bit.
ll grayCode(ll index) {
    assert(index >= 0);
    return index ^ (index >> 1);
}

// Convert a Gray code value back to its original index.
// Use after receiving/storing states in Gray-code order.
ll inverseGrayCode(ll gray) {
    assert(gray >= 0);
    ll value = 0;
    for (; gray; gray >>= 1) value ^= gray;
    return value;
}

/*
Common enumeration patterns:

All n-bit masks, for n < 63:
    for (ll mask = 0; mask < (1LL << n); ++mask) {
        // use mask
    }

Set bits of mask:
    for (ll rem = mask; rem; rem &= rem - 1) {
        int bit = __builtin_ctzll((unsigned long long)rem);
        // use bit
    }

Nonzero submasks of mask:
    for (ll sub = mask; sub; sub = (sub - 1) & mask) {
        // use sub
    }

Submasks including zero:
    for (ll sub = mask;; sub = (sub - 1) & mask) {
        // use sub
        if (sub == 0) break;
    }

All masks and their submasks is O(3^n): every bit is absent, only in mask, or in
both mask and submask.

Supermasks of mask inside n bits:
    ll lim = 1LL << n;
    for (ll super = mask; super < lim; super = (super + 1) | mask) {
        // use super
    }
*/

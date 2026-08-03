// Count integers x in [0, n] where bit `bit` is set.
// Use for range sums of AND/OR/XOR contributions or counting bit frequencies.
// Accepts nonnegative ll values and bit positions 0..62.
ll countOnesAtBitUpTo(ll n, int bit) {
    assert(n >= 0);
    assert(0 <= bit && bit < 63);

    ll halfBlock = 1LL << bit;
    if (bit == 62) {
        return n >= halfBlock ? n - halfBlock + 1 : 0;
    }

    ll block = halfBlock << 1;
    ll fullBlocks = n / block;
    ll rem = n % block;
    return fullBlocks * halfBlock + max(0LL, rem - halfBlock + 1);
}

// Count integers x in [left, right] where bit `bit` is set.
// Use when each bit contributes independently to the final answer.
ll countOnesAtBitInRange(ll left, ll right, int bit) {
    assert(0 <= left && left <= right);
    ll rightCount = countOnesAtBitUpTo(right, bit);
    ll beforeLeft = left == 0 ? 0 : countOnesAtBitUpTo(left - 1, bit);
    return rightCount - beforeLeft;
}

// Count total set bits among all integers in [0, n], capped at LLONG_MAX.
// Use for problems asking for sum of popcount over a prefix.
ll countTotalSetBitsUpTo(ll n) {
    assert(n >= 0);
    ll ans = 0;
    for (int bit = 0; bit < 63; ++bit) {
        ll add = countOnesAtBitUpTo(n, bit);
        if (LLONG_MAX - ans < add) return LLONG_MAX;
        ans += add;
    }
    return ans;
}

/*
Bit-pattern idea:
At bit b, values repeat in blocks:
    2^b zeros, then 2^b ones

So the cycle length is 2^(b+1). Count complete cycles, then add the ones in the
partial cycle. This is usually simpler and safer than iterating every number.
*/

// Return XOR of all integers in [0, n].
// Use for range XOR queries over consecutive integers. Pattern repeats by n % 4.
ll xorFromZero(ll n) {
    assert(n >= 0);
    switch (n & 3LL) {
        case 0: return n;
        case 1: return 1;
        case 2: return n + 1;
        default: return 0;
    }
}

// Return XOR of all integers in the inclusive range [left, right].
// Use when the range is consecutive, not an array range.
ll xorIntegerRange(ll left, ll right) {
    assert(0 <= left && left <= right);
    return xorFromZero(right) ^ (left == 0 ? 0 : xorFromZero(left - 1));
}


// Return the only value that appears once when every other value appears twice.
// Use the classic pair-cancellation trick.
ll singleNumberTwice(const vector<ll>& a) {
    ll ans = 0;
    for (ll x : a) ans ^= x;
    return ans;
}



/*
Useful XOR facts:
    x ^ 0 = x
    x ^ x = 0
    x ^ y = y ^ x
    (x ^ y) ^ z = x ^ (y ^ z)
    x ^ y ^ x = y

For nonnegative values in a growing window:
    (sum + x) - (xr ^ x) - (sum - xr) = 2 * (xr & x) >= 0
So sum - xor never decreases when you append a value. This often enables
two-pointers.

Prefer std::swap over XOR swap. XOR swap is harder to read and breaks when both
references point to the same object.
*/

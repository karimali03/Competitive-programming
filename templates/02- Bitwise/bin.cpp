// Convert a nonnegative integer to a string in base 2..36.
// Use for debugging masks or printing custom-base representations.
string toBase(ll num, int base = 2) {
    assert(num >= 0);
    assert(2 <= base && base <= 36);
    if (num == 0) return "0";

    const string digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string result;
    while (num > 0) {
        result.push_back(digits[num % base]);
        num /= base;
    }

    reverse(result.begin(), result.end());
    return result;
}

// Convert a fraction in [0, 1) to binary, stopping after maxBits digits.
// Use for interview-style binary fraction problems. Some fractions never end.
string fractionToBinary(long double num, int maxBits = 64) {
    if (num < 0 || num >= 1 || maxBits < 0) return "Error";

    string result = ".";
    for (int i = 0; i < maxBits && num != 0; ++i) {
        num *= 2;
        if (num >= 1) {
            result.push_back('1');
            num -= 1;
        } else {
            result.push_back('0');
        }
    }

    if (num != 0) result += "...";
    return result;
}

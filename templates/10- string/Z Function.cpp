/**
 * z[i] is the length of the longest common prefix between the string s
 * and the suffix of s starting at i.
 * By definition, z[0] = 0 (sometimes defined as n, but usually 0 in CP context).
 *
 * @complexity
 * Time: O(N) - Linear time complexity.
 * Space: O(N) - Linear space for the output vector.
 *
 * @use_cases
 * 1. Pattern Matching: Find occurrences of pattern P in text T.
 * - Construct string: S = P + "$" + T (where $ is a unique separator).
 * - Compute Z-function. If z[i] == length(P), a match starts at that position.
 * 2. String Periodicity: Check if a string is periodic.
 * - If i + z[i] == n and n % i == 0, then the prefix of length i is the period.
 * 3. String Compression: Find the shortest string that generates S by concatenation.
 * 4. Border Computation: Related to KMP's failure function.
 */
vector<int> z_function(const string& s) {
    int n = s.length();
    vector<int> z(n);
    // l and r define the "Z-box" (matches the prefix) [l, r]
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        // If i is inside the current Z-box, use previous values to initialize z[i]
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        // Naively extend the match as far as possible
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        // If we have extended past the current Z-box, update the box
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

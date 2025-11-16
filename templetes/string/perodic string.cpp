### Definition: String Periodicity
A string 's' is said to have a period of 'k' if the character at any position 'i' is the same as the character at position 'i + k'.
- s[0] = s[k] = s[2k] = ...
- s[1] = s[k+1] = s[2k+1] = ...
- ...and so on for all indices.

### Checking for Periodicity

There are several ways to check if a string or substring is periodic with period 'k':

1.  **Substring Equality Check:**
    A range [L, R] of a string is periodic with period 'k' if the substring from [L+k, R] is equal to the substring from [L, R-k].
    - `IF s[L+k ... R] == s[L ... R-k] THEN the range [L, R] has a period of 'k'`

2.  **Prefix-Suffix Overlap Check (using KMP Prefix Function):**
    - any prefix match with suffix in the stirng let p then string is perodic of (n - p)

### Application: String Compression
Periodicity is the key to string compression.

- If a string 's' of length 'n' has a period 'k' (as determined by the prefix-suffix check above), you must then check if 'k' divides 'n'.
- `IF 'k' divides 'n' (i.e., n % k == 0)`
- `THEN the string 's' can be compressed.` The shortest repeating block that forms 's' is the prefix of length 'k' (i.e., s[0 ... k-1]).
- `ELSE (if 'k' does not divide 'n')`
- `THEN no effective compression is possible,` and the shortest "compressed" string is 's' itself.

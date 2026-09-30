/*
    Motzkin Numbers
    ===============

    Sequence:
        M0 = 1
        M1 = 1
        M2 = 2
        M3 = 4
        M4 = 9
        M5 = 21
        M6 = 51
        ...

    ------------------------------------------------------------
    1) What is a Motzkin number?
    ------------------------------------------------------------

    Motzkin number M[n] counts many equivalent combinatorial objects.

    The most useful interpretations in competitive programming are:

    A) Motzkin paths
       A path of length n that:
         - starts at height 0
         - ends at height 0
         - never goes below height 0

       Allowed steps:
         Up    = (1, +1)
         Down  = (1, -1)
         Flat  = (1,  0)

    B) Non-crossing partial matching
       There are n points in order.

       Each point can:
         - stay unmatched
         - be matched with exactly one other point

       The matching edges must not cross.

       Number of configurations = M[n].

    C) Ordered unary-binary trees
       Ordered rooted trees where every node has:
         0, 1, or 2 children.

       Depending on the exact tree-size convention,
       Motzkin numbers count these structures by number of edges/nodes.

    ------------------------------------------------------------
    2) Main recurrence
    ------------------------------------------------------------

    Consider the first position in a Motzkin path.

    Case 1:
        First step is Flat.

        Remaining path has length n - 1.

        contribution = M[n - 1]

    Case 2:
        First step is Up.

        It must eventually have a matching Down step.

            Up + [inside] + Down + [after]

        Suppose "inside" has length i.
        Then "after" has length n - 2 - i.

        contribution =
            M[i] * M[n - 2 - i]

    Therefore:

        M[n] = M[n - 1]
             + sum_{i=0}^{n-2} M[i] * M[n-2-i]

    Base:
        M[0] = 1

    This gives an O(N^2) DP.

    ------------------------------------------------------------
    3) Recognition pattern in problems
    ------------------------------------------------------------

    If your recurrence becomes:

        dp[n] = dp[n - 1]
              + sum dp[i] * dp[n - 2 - i]

    strongly suspect Motzkin numbers.

    The dp[n - 1] term usually means:
        "leave the current object unused"
        OR
        "use a flat step"
        OR
        "give the current node exactly one child"

    The convolution term usually means:
        "pair current object with another object"
        OR
        "split into two independent recursive parts"
        OR
        "give the node two children"

    ------------------------------------------------------------
    4) Catalan vs Motzkin
    ------------------------------------------------------------

    Catalan numbers often appear when EVERYTHING must participate
    in a pair / binary structure.

        C[n] = sum C[i] * C[n - 1 - i]

    Example:
        Perfect non-crossing matching.

    Motzkin often appears when an element may additionally remain
    unused / single / flat.

        M[n] = M[n - 1]
             + sum M[i] * M[n - 2 - i]

    Useful memory:

        Catalan + "skip/single/unmatched option"
        -> often Motzkin.

    ------------------------------------------------------------
    5) Common uses
    ------------------------------------------------------------

    Look for Motzkin numbers in problems involving:

      - non-crossing partial matchings
      - non-crossing chords where vertices may stay unused
      - Motzkin paths: Up / Down / Flat
      - ordered trees with at most two children
      - recursive structures with:
            0 / 1 / 2 components
      - balanced-parentheses-like structures with a neutral action
      - some restricted arch / nesting problems

    Example: "Arches"
    -----------------
    A non-crossing perfect matching of 2n pillars is converted
    into an ordered forest of arches.

    Add one virtual root above all top-level arches.

    "No three sibling arches" means every node has at most
    two direct children.

    So we obtain a unary-binary ordered tree.

    Therefore the answer is M[n].

    ------------------------------------------------------------
    6) Faster recurrence
    ------------------------------------------------------------

    Motzkin numbers also satisfy:

        (n + 2) * M[n]
          = (2n + 1) * M[n - 1]
          + 3(n - 1) * M[n - 2]

    for n >= 2.

    Thus:

        M[n] =
          ((2n + 1) * M[n - 1]
          + 3(n - 1) * M[n - 2])
          / (n + 2)

    Under a prime modulus, division is multiplication by
    modular inverse.

    This lets us precompute M[0..N] in O(N).

    For MOD = 1e9+7 and N < MOD, all denominators n+2
    are invertible.

    ------------------------------------------------------------
    7) Code below
    ------------------------------------------------------------

    The program:
      - reads T
      - reads all n
      - precomputes Motzkin numbers up to max(n) in O(N)
      - prints M[n]

    This matches the "Arches" interpretation.
*/

#include <bits/stdc++.h>
using namespace std;

using int64 = long long;

static const int64 MOD = 1'000'000'007LL;


// ------------------------------------------------------------
// O(N^2) version
// Useful when you want the recurrence in its most natural form.
// ------------------------------------------------------------
vector<int64> motzkin_quadratic(int N) {
    vector<int64> M(N + 1, 0);
    M[0] = 1;

    for (int n = 1; n <= N; ++n) {
        M[n] = M[n - 1];

        for (int i = 0; i <= n - 2; ++i) {
            M[n] += M[i] * M[n - 2 - i] % MOD;
            if (M[n] >= MOD) M[n] -= MOD;
        }
    }

    return M;
}


// ------------------------------------------------------------
// O(N) version
//
// Uses:
//   (n + 2) M[n]
//     = (2n + 1) M[n-1] + 3(n-1) M[n-2]
//
// We precompute modular inverses:
//   inv[i] = i^{-1} mod MOD
//
// Formula below works because MOD is prime and i < MOD.
// ------------------------------------------------------------
vector<int64> motzkin_linear(int N) {
    vector<int64> M(N + 1, 0);

    M[0] = 1;
    if (N == 0) return M;

    M[1] = 1;

    // We need inverse up to N + 2.
    vector<int64> inv(N + 3, 1);

    for (int i = 2; i <= N + 2; ++i) {
        inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
    }

    for (int64 n = 2; n <= N; ++n) {
        int64 value = 0;

        value += ((2 * n + 1) % MOD) * M[n - 1] % MOD;
        value %= MOD;

        value += (3 * (n - 1) % MOD) * M[n - 2] % MOD;
        value %= MOD;

        M[n] = value * inv[n + 2] % MOD;
    }

    return M;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    vector<int> queries(T);
    int mx = 0;

    for (int &n : queries) {
        cin >> n;
        mx = max(mx, n);
    }

    // Preferred implementation.
    // O(maxN) preprocessing.
    vector<int64> M = motzkin_linear(mx);

    for (int n : queries) {
        cout << M[n] << '\n';
    }

    return 0;
}


/*
    Quick sanity check:

        n : 0  1  2  3  4   5   6
        M : 1  1  2  4  9  21  51

    ------------------------------------------------------------
    CP cheat sheet
    ------------------------------------------------------------

    Perfect non-crossing matching
        -> Catalan

    Non-crossing matching + unmatched points allowed
        -> Motzkin

    Up / Down / Flat path, never below zero
        -> Motzkin

    Ordered tree with 0 / 1 / 2 children
        -> Motzkin

    Recurrence:
        M[n] = M[n-1]
             + sum M[i] M[n-2-i]

        -> Motzkin
*/

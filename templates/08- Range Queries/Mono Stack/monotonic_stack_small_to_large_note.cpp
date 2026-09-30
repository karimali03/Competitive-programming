/*
    Monotonic Stack + Iterate Smaller Side = O(N log N)
    ===================================================

    Common situation
    ----------------
    For every index i, monotonic stack gives an interval [L[i], R[i]]
    where a[i] is the "owner" / chosen maximum (or minimum).

                    i
              /           \
        [L[i], i)       (i, R[i]]

    Suppose for each i we need to combine something from the left side
    with something from the right side.

    Instead of iterating both sides:
        O(left * right)

    iterate ONLY the smaller side and use a data structure/query
    for the whole larger side:

        left  = i - L[i] + 1
        right = R[i] - i + 1

        work(i) = min(left, right)

    Then, under the correct interval structure:

        sum_i min(left_i, right_i) = O(N log N)


    Why is the total O(N log N)?
    ------------------------------
    Use the "charging" / small-to-large argument.

    Fix one array position x.

    Suppose x is iterated while processing some pivot i because x lies
    in i's SMALLER side.

    If x is iterated again for an ancestor / larger owned interval,
    then the interval containing x must have grown by at least ~2x.

    Why?

    If a side of size S is the smaller side, then the opposite side
    has size >= S.

    Therefore the parent / larger interval has size at least about:

        S + S = 2S

    So every time x gets charged again, the relevant interval sizes grow like:

        1 -> 2 -> 4 -> 8 -> 16 -> ...

    They cannot exceed N.

    Hence one position can be charged only O(log N) times.

    There are N positions:

        total iterations = O(N log N)


    IMPORTANT: This is NOT true for arbitrary monotonic-stack boundaries.
    ---------------------------------------------------------------------

    Example:
        a = [5, 5, 5, 5, 5, ...]

    If for every i you use:
        nearest STRICTLY greater on the left
        nearest STRICTLY greater on the right

    then no greater element exists, so every i may get:

        L[i] = 0
        R[i] = N - 1

    and

        sum_i min(i + 1, N - i) = Theta(N^2)

    So "I used a monotonic stack" alone does NOT imply O(N log N).


    Required condition
    ------------------
    The intervals should have UNIQUE OWNERSHIP and behave like a
    Cartesian-tree hierarchy.

    Equal values must be tie-broken consistently.

    Usually this means asymmetric comparisons, e.g.

        left boundary  : nearest >=
        right boundary : nearest >

    or the reverse:

        left boundary  : nearest >
        right boundary : nearest >=

    This ensures that if multiple equal maxima exist, only one occurrence
    owns a given range.

    Then the owned intervals form a nested Cartesian-tree-like structure,
    and the small-to-large proof applies.


    Typical pattern
    ---------------

    for (int i = 0; i < n; i++) {
        int left  = i - L[i] + 1;
        int right = R[i] - i + 1;

        if (left <= right) {
            // Enumerate l in [L[i], i]
            // Query/process all r in [i, R[i]] using a DS.
            for (int l = L[i]; l <= i; l++) {
                // query larger right side
            }
        } else {
            // Enumerate r in [i, R[i]]
            // Query/process all l in [L[i], i] using a DS.
            for (int r = i; r <= R[i]; r++) {
                // query larger left side
            }
        }
    }


    Complexity
    ----------
    Number of enumerated positions:
        O(N log N)

    If each iteration performs a query costing O(F):

        total = O(N log N * F)

    Example:
        persistent binary trie query = O(log A) ~ 30 bits

        total = O(N log N log A)


    Mental takeaway
    ---------------
    If every pivot splits its UNIQUE owned interval into two sides:

        [ left side ] pivot [ right side ]

    and these intervals form a Cartesian-tree hierarchy:

        "iterate the smaller side, query the larger side"

    is often an O(N log N) total-work trick.

    This is the same general idea as:
        - small-to-large merging
        - DSU on tree style charging arguments
        - always processing the smaller component/set explicitly
*/
